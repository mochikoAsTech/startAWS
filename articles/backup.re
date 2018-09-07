= サーバのバックアップを取っておこう

この章ではAMIとEBSスナップショットを使ってサーバのバックアップをします。
サーバが壊れたときに助けてくれる「バックアップ」の存在。
今はあまりピンとこないかもしれませんが、大切なものがなくなったときにありがたみを知るはずです。

//pagebreak

== EBSスナップショットとAMI

@<chapref>{serverBuilding}ではEC2で立てたインスタンスにログインして色々な設定をしました。@<chapref>{apacheSetting}ではバーチャルホストを作りました。@<chapref>{wordPress}ではWordPressのインストールをしました。頑張っていっぱい設定しましたね。もしその設定が全部消えてしまって「1からやり直し」と言われたらどうなるでしょう？きっと心が折れてしまいます。

viで頑張って修正した設定ファイルやドキュメントルートに設置したWordPressのファイルなどはすべてEBSボリューム@<fn>{ebsStorage}に保存されています。ある日うっかり次のようなrmコマンド@<fn>{rm}を叩いてしまって「何もかも全部消えちゃった・・・バックアップもない・・・」と泣くことのないよう、EBSボリューム（つまりハードディスクに保存されたデータ）のバックアップを取っておきましょう。

//cmd{
rm -rf /
//}

//footnote[ebsStorage][EBSボリュームってなんだっけ？という方は、インスタンスを作るとき「ステップ4」でEBSボリュームの種類やサイズを選んだことを思い出してください。ちなみにOSがEBSボリュームではなく「インスタンスストア」というところにインストールされているインスタンスもあるのですがここではその説明は割愛します。]

//footnote[rm][ファイルを削除するrmコマンドにrecursive（再帰的）の-rオプションとforce（強制的）の-fオプションをつけて、削除対象に「/」（一番上のルートディレクトリ）を指定しているので「すべてのファイルを強制的に削除しろ」という意味のコマンドです。]

バックアップにはAmazon EBSのスナップショットというサービスを使用します。スナップショットは「ある時点」のEBSボリュームを丸ごと保存しておいてくれるので、うっかりデータを全削除してしまってもスナップショットを取っていた時点まで戻すことができます。

ただしスナップショットを取るときはデータの整合性を保つためにハードディスクへの読み書きを停止する必要があります。インスタンスを起動して使用しているままでもスナップショットを取ることはできますが、たとえば「MySQL（データベース）がトランザクション処理中でゴリゴリ書き込みをしている最中にスナップショットを取るとデータの整合性が取れない」といった可能性があり、ファイルシステムの完全性が保証できないので推奨されていません。ハードディスクへの読み書きがされない状態、つまりインスタンスを先にシャットダウンしておくか、もしくは対象となるEBSボリュームをアンマウント@<fn>{unmount}してからスナップショットを取るようにしましょう。

//footnote[unmount][ハードディスクをサーバから取り外すこと。]

マネジメントコンソールの左上にある「サービス」から、「コンピューティング」の下にある「EC2」（@<img>{startaws39}）をクリックしてください。

//image[startaws39][サービス＞コンピューティング＞EC2][scale=0.8]{
//}

「EC2」をクリックすると、EC2ダッシュボード（@<img>{startaws49}）が表示されます。左メニューの「インスタンス」をクリックしてください。

//image[startaws49][EC2ダッシュボードで「インスタンス」をクリック][scale=0.8]{
//}

@<chapref>{serverBuilding}でインスタンスを作るとき、ステップ1でAmazonマシンイメージ、略してAMIを選択したのを覚えていますか？先ほどはAMIというテンプレートのようなものを元にインスタンスを作りましたが、その逆でインスタンスから自分専用のカスタムAMIを作ることもできます。

インスタンスをAMIで丸ごとテンプレート化しておけば、そのAMIからインスタンスをいくつも複製できます。あるいは間違ってインスタンスを削除してしまったときに、AMIからインスタンスを作り直すことができます。

EBSスナップショットとAMIの関係がちょっと分かりにくいかも知れませんので、実際にやりながら理解していきましょう。

== インスタンスからAMIを作ろう

「start-aws-instance」というインスタンスを右クリック（@<img>{startaws50}）して、「イメージ」の「イメージの作成」をクリックします。

//image[startaws50][インスタンスを右クリックして「イメージの作成」をクリック][scale=0.8]{
//}

イメージ名に「start-aws-ami」と入力したら「イメージの作成」をクリック（@<img>{startaws51}）してください。

//image[startaws51][イメージ名に「start-aws-ami」と入力したら「イメージの作成」をクリック][scale=0.8]{
//}

「イメージの作成リクエストを受け取りました。」と表示（@<img>{startaws52}）されたら「閉じる」をクリックします。

//image[startaws52][「閉じる」をクリック][scale=0.8]{
//}

この「インスタンスを元にAMIを作成する」という作業をすると、実際は裏側で

 1. インスタンスを停止する
 2. インスタンスに紐づいているEBSボリュームのEBSスナップショットを取る
 3. そのEBSスナップショットを元にAMIを作る
 4. インスタンスを起動する

という複数の処理が実行@<fn>{stopInstance}されています。

//footnote[stopInstance][当たり前ですがインスタンスを停止している間、その上で動いていたウェブサイトは見られなくなります。AMIを作成する間（1～4の間）はサイトが落ちてしまう、ということです。]

少し待ってから左メニューで「スナップショット」をクリック（@<img>{startaws53}）してEBSスナップショットが生成されたか確認してみましょう。ステータスが「completed」になっていればEBSスナップショットの取得は完了しています。このEBSスナップショットに名前を付けておきましょう。Nameのところにカーソルを持っていくと鉛筆のマークが表示されますのでクリックしてください。

//image[startaws53][左メニューで「スナップショット」をクリックしてEBSスナップショットを確認][scale=0.8]{
//}

Nameに「start-aws-snapshot」と書いたらチェックボタンを押して（@<img>{startaws54}）ください。スナップショット名には日本語を使わないことをお勧めします。

//image[startaws54][作成したインスタンスのNameのところにある鉛筆マークをクリック][scale=0.8]{
//}

続いて左メニューで「AMI」をクリック（@<img>{startaws55}）してAMIが作成されたか確認してみましょう。「start-aws-ami」というAMIが作成されていますね。

//image[startaws55][左メニューで「AMI」をクリックしてAMIを確認][scale=0.8]{
//}

今後もしインスタンスを壊したりなくしたりして復元したくなったら、AMIを右クリックして「作成」をクリック（@<img>{startaws56}）すればこのAMIからインスタンスを復元できます。

//image[startaws56][インスタンスを復元したくなったらAMIを右クリックして「作成」をクリック][scale=0.8]{
//}