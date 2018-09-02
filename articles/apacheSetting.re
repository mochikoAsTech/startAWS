= ウェブサーバの設定をしよう

この章ではウェブサーバの設定を行います。
Apacheでバーチャルホストを作ってWordPressのサイトを表示してみましょう。

//pagebreak

== ウェルカムページを見てみよう

@<chapref>{serverBuilding}でサーバにApacheをインストールしました。インストールしただけでまだ何の設定もしていませんが、ウェルカムページと呼ばれるデフォルトのページが見られるはずです。しかしブラウザで「http://login.自分のドメイン/」を開いてウェルカムページを見ようとしたところ、「ページ読み込みエラー 接続がタイムアウトしました」「このサイトにアクセスできません。login.自分のドメイン からの応答時間が長すぎます。」といったエラーメッセージが表示（@<img>{startaws57}）されてページを見ることはできませんでした。

//image[startaws57][http://login.自分のドメイン/ が見られなかった][scale=0.8]{
//}

これはインスタンスの手前に居るセキュリティグループ@<fn>{securityGroup}が「SSH（ポート番号22番）の通信しか通さない」という設定になっていて、HTTP（ポート番号80番）のリクエストを遮断していることが原因です。ポート番号とは、セキュリティグループという防火壁やサーバという家についているドアのようなものだと思ってください。同じサーバを訪問するときでもSSHは22番のドアを通るし、HTTPは80番のドアを通るし、HTTPSは443番のドアを通ります。

//footnote[securityGroup][セキュリティグループはいわゆる「ファイアウォール」のことです。セキュリティグループってどんなものだったっけ？という方は@<chapref>{serverBuilding}でインスタンスを作るとき「ステップ6」で設定したことを思い出してください。]

=== セキュリティグループで80番ポートの穴あけをしよう

ウェルカムページが見られるように、セキュリティグループで「HTTP（ポート番号80番）」の穴あけをしましょう。マネジメントコンソールの左上にある「サービス」から、「コンピューティング」の下にある「EC2」（@<img>{startaws58}）をクリックしてください。

//image[startaws58][サービス＞コンピューティング＞EC2][scale=0.8]{
//}

「EC2」をクリックすると、EC2ダッシュボード（@<img>{startaws59}）が表示されます。左メニューの「セキュリティグループ」をクリックしてください。「ec2-security-group」をクリックして「インバウンド」タブを見ると、現状は通信を許可する対象に「SSH（ポート番号22番）」しか含まれていません。「インバウンド」タブの「編集」をクリックします。

//image[startaws59][EC2ダッシュボードで「セキュリティグループ」をクリック][scale=0.8]{
//}

「ルールの追加」をクリックしたらタイプは「HTTP」を選択（@<img>{startaws60}）します。ソースが「カスタム」になり「0.0.0.0/0, ::/0」と入力されるので、カンマから後ろを消して「0.0.0.0/0」にしてください。入力できたら「保存」をクリックします。

//image[startaws60][タイプは「HTTP」、ソースは「0.0.0.0/0」にして「保存」をクリック][scale=0.8]{
//}

「インバウンド」タブでHTTPが追加（@<img>{startaws61}）されていたら穴あけ作業は完了です。

//image[startaws61][「インバウンド」タブでHTTPが追加されていたら穴あけ完了][scale=0.8]{
//}

もう一度ブラウザで「http://login.自分のドメイン/」を開いてみましょう。「Amazon Linux AMI Test Page」と書かれたウェルカムページが表示されるはずです。

//image[startaws62][Amazon Linux AMI Test Pageが表示された][scale=0.8]{
//}

== 自分のサイト用にバーチャルホストを作ろう

=== バーチャルホストとは？

=== バーチャルホストを設定しよう

=== ドキュメントルートを作成

=== index.htmlを置いてみよう

=== curlでページを確認しよう

== Route53でAレコードを追加しよう

=== ブラウザでページを見てみよう
