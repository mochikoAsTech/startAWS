= ELBとAuto Scalingで複数台のサーバを運用しよう

この章ではロードバランサーの設定や、サーバが停止してしまったときに自動復旧するAuto Scalingの設定をします。

//pagebreak

== ELBはなんのためにある？

ウェブサーバやデータベースサーバなどのインフラ環境を構築するときには「ここが壊れたり止まったりしたらサービス全体が停止する」というSPOF@<fn>{spof}をつぶしておくことが大切です。

//footnote[spof][Single Point of Failureの略。「ここが壊れたらシステム全体が停止する」という単一障害点のこと。]

皆さんが本著で構築した環境は「EC2のウェブサーバ1台＋RDSのデータベースサーバ1台」という低コストのお手軽構成ですので、ウェブサーバもデータベースサーバもどちらもSPOFになっています。たとえばEC2のウェブサーバが壊れたらその瞬間にWordPressのサイトは見られなくなります。@<fn>{break}

//footnote[break][サーバが壊れると言われてもピンと来ないかも知れませんが、ホストサーバのハードウェアが壊れてしまえば、当然その上で動いていたゲストサーバ（EC2のインスタンス）も影響を受けて「突然うんともすんとも言わなくなった！」状態になることはあります。ただその場合もOSやデータが入ったEBSボリュームは生きているので、EC2ダッシュボードを開いて手動でインスタンスを起動させれば別のホストサーバ上でまた元気に働きだすはずです。]

このSPOFをなくすための手段の1つとしてELB@<fn>{elb}、いわゆる負荷分散のためのロードバランサーのサービスがあります。もしEC2のウェブサーバが2台あって、その手前のロードバランサーがアクセスを2台に振り分けていたら、1台が停止している間ももう1台が応答できるのでサイトは停止しません。

//footnote[elb][Elastic Load Balancingの略。]

「予算がないのでウェブサーバを2台用意するのは無理です」とか「小規模なサイトなのでそこまでの冗長性は求めていません」という場合でもELBは役に立ちます。ELBを使って1台のウェブサーバにアクセスを流していた場合、Auto Scaling（オートスケーリング）というサービスを使うことで、その1台が死んでしまったときに自動でインスタンスを立ててサイトを自動復旧させてくれます。

他にもELBを使うと無料でSSL証明書を取得してサイトを楽にHTTPS化できるなど色々なメリットがあります。ELBは無料利用枠にも含まれていますので、ここではELBからEC2のインスタンスへアクセスを流すロードバランシングの設定をしてみましょう。

== ロードバランサーを作ろう

それではマネジメントコンソールの左上にある「サービス」から、「コンピューティング」の下にある「EC2」（@<img>{startaws129}）をクリックしてください。

//image[startaws129][サービス＞コンピューティング＞EC2][scale=0.8]{
//}

「EC2」をクリックすると、EC2のダッシュボード（@<img>{startaws130}）が表示されます。左メニューの「ロードバランサー」をクリックしてください。

//image[startaws130][左メニューの「ロードバランサー」をクリック][scale=0.8]{
//}

「ロードバランサーの作成」をクリック（@<img>{startaws131}）します。

//image[startaws131][「ロードバランサーの作成」をクリック][scale=0.8]{
//}

=== ロードバランサーの種類の選択

ロードバランサーにもいくつか種類があるのですが、今回はいちばん左の「Application Load Balancer」を使います。「作成」をクリック（@<img>{startaws132}）してください。

//image[startaws132][「Application Load Balancer」の「作成」をクリック][scale=0.8]{
//}

ここからは6つのステップでロードバランサーを作成していきます。

=== ステップ 1: ロードバランサーの設定

名前に「start-aws-elb」と入力（@<img>{startaws133}）したらそのまま下の方へスクロールします。

//image[startaws133][名前に「start-aws-elb」と入力][scale=0.8]{
//}

アベイラビリティーゾーンはすべてにチェック（@<img>{startaws134}）を入れて、「次の手順: セキュリティ設定の構成」をクリックします。

//image[startaws134][AZはすべてにチェックを入れて「次の手順: セキュリティ設定の構成」をクリック][scale=0.8]{
//}

=== ステップ 2: セキュリティ設定の構成

いきなり黄色で「ロードバランサーのセキュリティを向上させましょう。ロードバランサーは、いずれのセキュアリスナーも使用していません。」と表示（@<img>{startaws135}）されましたが、これは「HTTPじゃなくてもっとセキュアなHTTPSにした方がいいよ」とアドバイスをしてくれているだけですので、今はそのままスルーで構いません。「次の設定: セキュリティグループの設定」をクリックします。

//image[startaws135][「次の設定: セキュリティグループの設定」をクリック][scale=0.8]{
//}

=== ステップ 3: セキュリティグループの設定

「セキュリティグループの割り当て」で「新しいセキュリティグループを作成する」を選択（@<img>{startaws136}）します。「セキュリティグループ名」と「説明」は次のように入力してください。（@<table>{elbSecurityGroup}）

//table[elbSecurityGroup][セキュリティグループの設定]{
セキュリティグループ名	elb-security-group
説明	HTTP Allow from anywhere
//}

続いて「ここからのアクセスのみを通す」というルールを設定します。ルールはタイプが「HTTP」で、ソースを「カスタム」の「0.0.0.0/0」にします。

//image[startaws136][セキュリティグループを設定したら「次の手順: ルーティングの設定」をクリック][scale=0.8]{
//}

これはロードバランサーの手前にあるセキュリティグループ（ファイアウォール）を「HTTP（ポート番号80番）ならどこからのリクエストでも通す」という設定にしています。ルールを設定したら「次の手順: ルーティングの設定」をクリックします。

=== ステップ 4: ルーティングの設定

ターゲットグループというのはロードバランサーの分散先となるサーバのグループのことです。つまり「このグループに入っているインスタンスにアクセスを割り振ります」ということですね。

名前に「elb-target-group」と入力（@<img>{startaws137}）したら、それ以外の設定@<fn>{healthcheck}はすべてのそのままで構いません。「次の手順: ターゲットの登録」をクリックします。

//image[startaws137][名前に「elb-target-group」と入力したら「次の手順: ターゲットの登録」をクリック][scale=0.8]{
//}

//footnote[healthcheck][ちなみにこのページで設定している「ヘルスチェック」とは、名前のとおりロードバランサーがターゲットグループのインスタンスに対して行う「ねぇウェブサーバ生きてる？ねぇねぇ生きてる？」という死活チェックのことです。このチェックに対してウェブサーバが応答をしなくなると「あ、死んでるからこのウェブサーバにアクセス流すのやめよう」となって負荷分散対象から除外されるのです。]

=== ステップ 5: ターゲットの登録

下部の「インスタンス」にある「start-aws-instance」にチェック（@<img>{startaws138}）を入れたら「登録済みに追加」をクリックします。

//image[startaws138][「start-aws-instance」にチェックを入れたら「登録済みに追加」をクリック][scale=0.8]{
//}

上部の「登録済みターゲット」に「start-aws-instance」が表示（@<img>{startaws139}）されたら「次の手順: 確認」をクリックします。

//image[startaws139][「登録済みターゲット」に「start-aws-instance」が表示されたら「次の手順: 確認」をクリック][scale=0.8]{
//}

=== ステップ 6: 確認

設定内容を確認したら「作成」をクリック（@<img>{startaws140}）します。

//image[startaws140][設定内容を確認したら「作成」をクリック][scale=0.8]{
//}

「ロードバランサーを正常に作成しました」と表示（@<img>{startaws141}）されたら「閉じる」をクリックします。

//image[startaws141][設定内容を確認したら「作成」をクリック][scale=0.8]{
//}

これでロードバランサーの作成は完了です。（@<img>{startaws142}）

//image[startaws142][ロードバランサーの作成は完了][scale=0.8]{
//}

=== ヘルスチェックの確認をしよう

ロードバランサーの作成が完了したら、EC2ダッシュボードの左メニューで「ターゲットグループ」をクリック（@<img>{startaws162}）して「elb-target-group」の「ターゲット」タブを確認してみましょう。

//image[startaws162][「start-aws-instance」のステータスを確認してみよう][scale=0.8]{
//}

ターゲットである「start-aws-instance」のステータスがhealthyになっていれば、ロードバランサーからの「ねぇ生きてる？」に対してEC2で作ったウェブサーバが「生きてる！」と元気に応答しているということです。

もしステータスが「unhealthy」になっていたら「ねぇ生きてる？」にちゃんと応答できていませんので、次の確認をしましょう。

 * EC2のインスタンス（start-aws-instance）が起動しているか？
 * EC2のインスタンスでApacheが起動しているか？
 * EC2の手前にいるセキュリティグループ（ec2-security-group）でHTTP（ポート番号80番）のアクセスを許可しているか？

== WordPressのサイトを表示する経路を変更しよう

=== 「www.自分のドメイン」と紐づくIPアドレスを変更しよう

EC2ダッシュボードの左メニューで「ロードバランサー」をクリック（@<img>{startaws180}）したら「start-aws-elb」の「説明」タブにある「DNS名」をコピーしてください。

//image[startaws180][「start-aws-elb」の「説明」タブにある「DNS名」をコピー][scale=0.8]{
//}

このDNS名をそのままブラウザで開く（@<img>{startaws181}）とWordPressのサイトが表示されます。

//image[startaws181][DNS名をそのままブラウザで開くとWordPressのサイトが表示される][scale=0.8]{
//}

これでロードバランサーを経由してWordPressのサイトが見られることが確認できたので、Route53でDNSの変更を行いましょう。

=== Route53でAレコードをAliasに変更しよう

マネジメントコンソールの左上にある「サービス」から、「ネットワーキング＆コンテンツ配信」の下にある「Route53」（@<img>{startaws182}）をクリックしてください。

//image[startaws182][サービス＞ネットワーキング＆コンテンツ配信＞Route53][scale=0.8]{
//}

Route53ダッシュボードを開いたらDNS managementの「Hosted zones」をクリック（@<img>{startaws183}）します。

//image[startaws183][「Hosted zones」をクリック][scale=0.8]{
//}

Domain Nameの自分のドメイン名（筆者の場合はstartdns.fun）をクリック（@<img>{startaws184}）します。

//image[startaws184][自分のドメイン名をクリック][scale=0.8]{
//}

「www.自分のドメイン名」（筆者の場合は「www.startdns.fun」）をクリック（@<img>{startaws185}）すると右側に既存のAレコードが表示されます。

//image[startaws185][「www.自分のドメイン名」をクリックすると右側に既存のAレコードが表示される][scale=0.8]{
//}

現状はvalueにEC2インスタンスのElastic IPが設定されています。つまりこのままだと「@<href>{http://www.自分のドメイン名/}」を開いたときに、ロードバランサー経由ではなく直接EC2インスタンスへ「ウェブページを見せて！」とリクエストが行ってしまい、ロードバランサーを作成した意味がありません。「www.自分のドメイン名」と紐づくIPアドレスをElastic IPからELBに変更しましょう。

Aliasを「No」から「Yes」に変更して「Alias Target」の「Enter targe name」と書かれたところをクリック（@<img>{startaws186}）すると、プルダウンで「start-aws-elb」のDNS名@<fn>{dnsName}が表示されるのでクリックしてください。

//image[startaws186][「www.自分のドメイン名」をクリックすると右側に既存のAレコードが表示される][scale=0.8]{
//}

//footnote[dnsName][さっきブラウザで開いでWordPressのサイトが見られたDNS名です。]

「Alias Target」が「start-aws-elb」になったら「Save Record Set」をクリック（@<img>{startaws187}）します。

//image[startaws187][「Alias Target」が「start-aws-elb」になったら「Save Record Set」をクリック][scale=0.8]{
//}

これで「www.自分のドメイン名」と紐づくIPアドレスがElastic IPからELBに変わりました。

//image[startaws188][「www.自分のドメイン名」と紐づくIPアドレスがElastic IPからELBに変わった][scale=0.8]{
//}

それではEC2のインスタンスでdigコマンド@<fn>{dig}を叩いてAレコードの設定が変更されたか確認してみましょう。Windowsの方はRLoginを起動して「start-aws-instance」に接続してください。Macの方はターミナルで次のコマンドを実行してください。

//footnote[dig][digコマンドについては「DNSをはじめよう」の第4章「digとwhoisを叩いて学ぶDNS」を参照してください。]

//cmd{
ssh ec2-user@login.自分のドメイン名 -i ~/Desktop/start-aws-keypair.pem
//}

「Amazon Linux AMI」と表示されたらログイン完了です。次のコマンドを叩いてみてください。

//cmd{
$ dig www.自分のドメイン名 +short
//}

筆者ならドメイン名が「startdns.fun」なので次のようになります。

//cmd{
$ dig www.startdns.fun +short
54.178.188.244
54.64.131.11
//}

このようにIPアドレスが2つ返ってきたらAレコードの設定はちゃんと変更されています。これで「@<href>{http://www.自分のドメイン名/}」を開いたときに、ロードバランサーを経由してWordPressのサイトが表示されるようになりました。

=== HTTPを通すのはELB経由のアクセスだけにしよう

Aレコードを変更したことで、今後は「サイトを見たい人→ロードバランサー→EC2のインスタンス」という経路だけを使うことになるので「サイトを見たい人→EC2のインスタンス（Elastic IP）」という不要な経路はふさいでおきましょう。

それではマネジメントコンソールの左上にある「サービス」から、「コンピューティング」の下にある「EC2」（@<img>{startaws189}）をクリックしてください。

//image[startaws189][サービス＞コンピューティング＞EC2][scale=0.8]{
//}

EC2のダッシュボードが表示（@<img>{startaws190}）されたら左メニューの「セキュリティグループ」をクリックします。「ec2-security-group」のインバウンドタブをクリックすると、現状は「@<ttb>{HTTP（ポート番号80番）はどこからのリクエストでも通す}」という設定になっています。ここを「HTTP（ポート番号80番）はELB経由のリクエストのみ通す」という設定にしたいので「編集」をクリックしてください。

//image[startaws190][「ec2-security-group」のインバウンドタブをクリック][scale=0.8]{
//}

HTTPの「ソース」に書いてある「0.0.0.0/0」を消して、代わりに「elb」と入力（@<img>{startaws191}）するとプルダウンで「elb-security-group」が表示されますのでクリックしてください。

//image[startaws191][「elb」と入力すると「elb-security-group」が表示されるのでクリック][scale=0.8]{
//}

ソースが「elb-security-group」の（@<img>{startaws192}）グループIDになったら「保存」をクリックします。

//image[startaws192][ソースが「elb-security-group」のグループIDになったら「保存」をクリック][scale=0.8]{
//}

これでEC2インスタンスの手前にいるセキュリティグループが「@<ttb>{HTTP（ポート番号80番）はELB経由のリクエストのみ通す}」という状態（@<img>{startaws193}）になりました。

//image[startaws193][セキュリティグループが「HTTP（ポート番号80番）はELB経由のリクエストのみ通す」という状態になった][scale=0.8]{
//}

ブラウザでEC2インスタンスに紐づいているElastic IPを直接叩く（@<img>{startaws193}）とセキュリティグループに阻まれてWordPressのサイトは表示されません。

//image[startaws195][Elastic IPを直接叩くとセキュリティグループに阻まれてサイトが表示されない][scale=0.8]{
//}

でもELBを経由する「@<href>{http://www.自分のドメイン名/}」を開いたときはちゃんと表示（@<img>{startaws194}）されます。

//image[startaws194][ELBを経由する「@<href>{http://www.自分のドメイン名/}」を開いたときはちゃんと表示される][scale=0.8]{
//}

== Auto Scaling

AWS Auto Scaling（オートスケーリング）はサーバの自動拡張・縮小をしてくれるサービスです。アクセスが増えてきてウェブサーバ1台ではさばききれなくなったらAuto Scalingが自動的に追加のサーバを立ててくれますし、アクセス数が落ち着いてきて1台で十分な状態になったら自動的に不要なサーバを削除してくれます。

しかし本著ではAuto Scalingを拡張や縮小ではなく「インスタンス数の維持」のために利用します。何か問題が起きてEC2のインスタンスが停止してしまっても、Auto Scalingによって新たにインスタンスが1台立てられてウェブサイトが自動復旧する状態を目指します。

=== 起動設定を作成しよう

EC2ダッシュボードの左メニューで「AUTO SCALING」の下にある「起動設定」をクリック（@<img>{startaws163}）してください。この「起動設定」ではAuto Scalingが自動で立てるEC2インスタンスのAMIやインスタンスタイプを指定します。続いて「起動設定の作成」をクリックしてください。

//image[startaws163][「起動設定」で「起動設定の作成」をクリック][scale=0.8]{
//}

ここからは6つのステップで起動設定を作成していきます。

==== 1. AMI の選択

「マイAMI」をクリックしたら@<chapref>{backup}で作成した「start-aws-ami」というAMIを選択（@<img>{startaws164}）します。

//image[startaws164][「マイAMI」で「start-aws-ami」を選択][scale=0.8]{
//}

==== 2. インスタンスタイプの選択

インスタンスタイプは現在のインスタンスと同じ「t2.micro」が選択されているので、そのまま「次の手順: 詳細設定」をクリック（@<img>{startaws165}）します。

//image[startaws165][「t2.micro」が選択されているのでそのまま「次の手順: 詳細設定」をクリック][scale=0.8]{
//}

==== 3. 詳細設定

「名前」には現在のインスタンスと同じ「start-aws-instance」を入力して「次の手順: ストレージの追加」をクリック（@<img>{startaws166}）します。

//image[startaws166][「名前」に「start-aws-instance」を入力して「次の手順: ストレージの追加」をクリック][scale=0.8]{
//}

==== 4. ストレージの追加

現在のインスタンスと同じ8GBのままでいいので、そのまま「次の手順: セキュリティグループの設定」をクリック（@<img>{startaws167}）してください。

//image[startaws167][そのまま「次の手順: セキュリティグループの設定」をクリック][scale=0.8]{
//}

==== 5. セキュリティグループの設定

「既存のセキュリティグループを選択する」をクリック（@<img>{startaws168}）して、現在のインスタンスと同じ「ec2-security-group」にチェックを入れたら「確認」をクリックします。

//image[startaws168][「ec2-security-group」にチェックを入れたら「確認」をクリック][scale=0.8]{
//}

==== 6. 確認

「起動設定」の内容を確認したら「起動設定の作成」をクリック（@<img>{startaws169}）してください。

//image[startaws169][「起動設定」の内容を確認したら「起動設定の作成」をクリック][scale=0.8]{
//}

==== 既存のキーペアを選択

「既存のキーペアを選択するか、新しいキーペアを作成します」と表示（@<img>{startaws170}）されました。これはAuto Scalingが自動で立てるEC2インスタンスに、既存のキーペアの鍵穴を設置しますか？それとも新しくキーペアを作り直してその鍵穴を設置しますか？と聞かれています。Auto Scalingで自動起動したインスタンスにも同じ鍵でSSHログインしたいので「既存のキーペアを選択」で「start-aws-keypair」になっていることを確認したら、チェックボックスにチェックを入れて「起動設定の作成」をクリックしてください。

//image[startaws170][チェックボックスにチェックを入れて「起動設定の作成」をクリックク][scale=0.8]{
//}

「起動設定が正常に作成されました: start-aws-instance」と表示されたら「この起動設定を使用してAuto Scalingグループを作成する」をクリック（@<img>{startaws171}）します。

//image[startaws171][起動設定が作成できたら「この起動設定を使用してAuto Scalingグループを作成する」をクリック][scale=0.8]{
//}

=== Auto Scalingグループを作成しよう

「起動設定」ができたら続いて「Auto Scalingグループ」を作成します。Auto ScalingグループはEC2インスタンスのグループのことで、このグループで常に維持したいインスタンスの数などを設定します。インスタンスの数はここで設定した最小数と最大数の間で増減します。

ここからは5つのステップでAuto Scalingグループを作成していきます。

==== 1. Auto Scaling グループの詳細設定

グループ名に「start-aws-autoscaling-group」と入力して、サブネットは既存のEC2インスタンスと同じ「ap-northeast-1a」を選択したら「高度な詳細」をクリック（@<img>{startaws172}）します。

//image[startaws172][グループ名に「start-aws-autoscaling-group」と入力したら「高度な詳細」をクリック][scale=0.8]{
//}

「高度な詳細」では「ロードバランシング」にチェック（@<img>{startaws173}）を入れます。「ターゲットグループ」で「elb-target-group」を選択して、「ヘルスチェックのタイプ」は「ELB」を選択します。これでELBからのヘルスチェックに対してインスタンスが応答しなくなったら、Auto Scalingによって自動的にインスタンスが立てられることになります。すべて設定したら「次の手順: スケーリングポリシーの設定」をクリックします。

//image[startaws173][設定したら「次の手順: スケーリングポリシーの設定」をクリック][scale=0.8]{
//}

==== 2. スケーリングポリシーの設定

本著ではAuto Scalingを拡張や縮小ではなく「インスタンス数の維持」のために利用したいので、「このグループを初期のサイズに維持する」のままで「次の手順: 通知の設定」をクリック（@<img>{startaws174}）します。

//image[startaws174][何も変更せず「次の手順: 通知の設定」をクリック][scale=0.8]{
//}

==== 3. 通知の設定

「通知の追加」をクリックします。（@<img>{startaws175}）

//image[startaws175][「通知の追加」をクリック][scale=0.8]{
//}

「通知の送信先」に自分の名前、「受信者」に自分のメールアドレス@<fn>{mailAddress}を記入したら「次の手順: タグを設定」をクリック（@<img>{startaws176}）します。

//footnote[mailAddress][メールアドレスの確認のため「AWS Notification - Subscription Confirmation」というメールが届きます。メール本文中にある「Confirm subscription」というリンクを踏んでおいてください。]

//image[startaws176][自分の名前とメールアドレスを記入したら「次の手順: タグを設定」をクリック][scale=0.8]{
//}

==== 4. タグを設定

何も変更せず「確認」をクリック（@<img>{startaws177}）します。

//image[startaws177][何も変更せず「確認」をクリック][scale=0.8]{
//}

==== 5. 確認

内容を確認したら「Auto Scalingグループの作成」をクリック（@<img>{startaws178}）してください。

//image[startaws178][内容を確認したら「Auto Scalingグループの作成」をクリック][scale=0.8]{
//}

「Auto Scalingグループが正常に作成されました」と表示されたら「閉じる」をクリック（@<img>{startaws179}）します。

//image[startaws179][「閉じる」をクリック][scale=0.8]{
//}

これで「start-aws-autoscaling-group」というAuto Scalingグループが作成できました。早速インスタンスを削除して自動復旧するかテストしてみましょう。

=== インスタンスを削除して自動復旧を試してみよう

それではインスタンスを停止してもサイトが自動復旧するのか試してみましょう。まずブラウザで「@<href>{http://www.自分のドメイン名/}」を開いてサイトが表示（@<img>{startaws199}）されていることを確認します。

//image[startaws199][@<href>{http://www.自分のドメイン名/}」を開くとサイトが表示される][scale=0.8]{
//}

続いてEC2ダッシュボードの左メニューで「インスタンス」をクリックしたら「start-aws-instance」を右クリックして、「インスタンスの状態」から「削除」（@<img>{startaws198}）をクリックしてみましょう。@<fn>{ami}

//footnote[ami][もしAuto Scalingの設定に失敗していて自動復旧しなくても、手動でAMIからインスタンスを作り直せば復旧できるので大丈夫です。]

//image[startaws198][「インスタンスの状態」から「削除」をクリック][scale=0.8]{
//}

恐ろしい警告が表示（@<img>{startaws200}）されますが「はい、削除する」をクリックします。

//image[startaws200][「はい、削除する」をクリック][scale=0.8]{
//}

インスタンスを削除すると状態がまず「shutting-down」に変わります。再びブラウザで「@<href>{http://www.自分のドメイン名/}」を見てみましょう。サイトがウェブサーバごといなくなってしまったので「503 Service Temporarily Unavailable」と表示（@<img>{startaws201}）されています。

//image[startaws201][再び@<href>{http://www.自分のドメイン名/}」を開くと「503 Service Temporarily Unavailable」と表示される][scale=0.8]{
//}

停止から1分後、「Auto Scaling: launch for group "start-aws-autoscaling-group"」という件名のメール（@<img>{startaws202}）が届きました。どうやらAuto ScalingによってAMIからインスタンスが生成されたようです。

//image[startaws202][Auto Scalingによるインスタンスの追加を知らせるメールが届いた][scale=0.8]{
//}

左メニューで「インスタンス」をクリックすると、先ほど削除したインスタンスの状態は「terminated」@<fn>{terminated}になり、その下に新たなインスタンスが表示（@<img>{startaws204}）されています。

//footnote[terminated][インスタンスの状態が「terminated」になってからしばらくすると一覧に表示されなくなります。]

//image[startaws204][先ほど削除したインスタンスの下に新たなインスタンスが表示されている][scale=0.8]{
//}

停止から3分後、もう一度ブラウザで「@<href>{http://www.自分のドメイン名/}」を開いてみると、見事にサイトは復旧していました。

//image[startaws203][もう一度@<href>{http://www.自分のドメイン名/}」を開くとサイトが復旧していた！][scale=0.8]{
//}

このようにインスタンスを削除したことで一時的にWordPressのサイトが見られなくなりましたが、すぐにAuto Scalingによってインスタンスが生成されサイトも自動復旧しました。このとき記事データはRDS（データベースサーバ）に、画像はS3にあるので何もかも元通りに表示されます。

但しAuto Scalingでインスタンスが自動生成された場合、SSHログイン時に使っていたElastic IPだけは新しいインスタンスに自動で紐づきません。Elastic IPは元々紐づいていたインスタンスを失って宙ぶらりんな状態になっています。左メニューの「Elastic IP」をクリックして、新しいEC2インスタンスに「アドレスの関連付け」をしてやれば再びSSHログインできるようになります。

//image[startaws205][新しいEC2インスタンスに宙ぶらりんなElastic IPの「アドレスの関連付け」をしてあげよう][scale=0.8]{
//}

ウェブサーバを削除しても数分で何事もなかったかのように自動で直るなんてすごくないですか？これでAuto ScalingでEC2インスタンスを自動復旧させる設定はおしまいです。