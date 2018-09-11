= データベースサーバを立てよう

WordPressを使うにはMySQLというデータベースが必要です。
この章ではRDSでデータベースサーバを立てましょう。

//pagebreak

== WordPressにはデータベースが必要

=== CMSとは？

こちらをご覧ください！このおしゃれなブログはWordPressというCMSで動いています。（@<img>{startaws124}）

//image[startaws124][WordPressで作ったおしゃれなブログ][scale=0.8]{
//}

CMSとはContents Management Systemの略で、@<ttb>{ウェブサイトのコンテンツを管理したり、ウェブページを更新したりするためのソフト}のことです。CMSがあればHTMLやCSSなどを自分で直接編集しなくても、Wordのように文章を書いてレイアウトを整え「更新」をクリックするだけでサイトが更新できます。

CMSにはWordPress（ワードプレス）とMovable Type（ムーバブル・タイプ）というツートップがあるのですが、どちらも個人利用であれば無料で使うことができます。今回はCMS界でトップシェアを誇るWordPressを使えるように環境を構築していきましょう。

WordPressの管理画面でブログ記事を書いて保存すると、記事のデータはデータベースに保存されます。そしてページを表示するときはデータベースからデータを取ってきて画面が構成されます。そのためWordPressを使うにはMySQLというデータベースが必須となっています。

===[column] 【コラム】MySQLとMariaDB

データベースはOracle DatabaseやPostgreSQLなどMySQL以外にも色々な種類があるのですが、その中でMySQLはもっとも普及しているデータベースでシェア全体の8割以上を占めています。

MySQLは元々はMySQL ABという会社が開発してオープンソースで公開していましたが、2008年にMySQL ABがSun Microsystemsに買収され、さらに2009年にSunがOracleに買収されたため現在はOracleのものになっています。Oracleに買収された後もありがたいことにMySQLは引き続きオープンソースで公開されており現在も無償で使えますが、OracleはもともとOracle Databaseという有償のデータベースも販売しているためMySQLはその競合にあたり、今は平気でもいつかはサポートが終了したりオープンソースで公開されなくなるのでは？という懸念もあります。

またMySQLを最初に作った開発者はすでにOracleを離れており、MariaDBというMySQLから派生した別のデータベースを開発しています。このことからLinuxのディストリビューションであるCentOS 6やAmazon LinuxではMySQLが採用されていましたが、CentOS 7及びAmazon Linux 2からはMariaDBに切り替わっています。しかもyumでMySQLをインストールしようとすると、何も言わずにそーっとMariaDBがインストールされる落とし穴仕様です。サーバの仕様を「OSはCentOS 7でDBはMySQLです」と決めていたのに、環境構築後によくよく確認したら入っていたのはMariaDBだった、というようなことにならないようご注意ください。

上記のような背景から引き続きMySQLを使うべきか、今後はMariaDBに切り替えるべきかという懸念はここ数年ずっとある気がしますが、個人的にはOracleが「MySQLの開発とサポートやめた！」と言い出すまでは積極的にMariaDBに切り替える理由もないかな、という気持ちです。

ちなみにWordPressはMySQLでもMariaDBでも動きますので、今回は深く考えずにMySQLを使いましょう。

===[/column]

=== EC2にインストールするか？RDSを使うか？

AWSでMySQLを使いたいとき、EC2でインスタンスを作成してyumでMySQLをインストールする@<fn>{apache}方法と、Amazon RDSというサービスを使う方法があります。

//footnote[apache][サーバにApacheをインストールしてウェブサーバを作ったのと同じように、MySQLをインストールしてデータベースサーバを作る、ということです。既にMySQLがインストールされたAMIからインスタンスを作ることもできます。]

Amazon RDSはAmazon Relational Database Serviceの略で、ざっくり言うとデータベースを提供してくれるサービスです。データベースに接続することはできますが、MySQLが動いているサーバにSSHでログインすることはできません。RDSではデータベースエンジンとしてMySQLだけでなくAmazon Aurora@<fn>{aurora}、Microsoft SQL Server、Oracle、PostgreSQLなども選択可能です。

//footnote[aurora][本当は「MySQLの最大5倍のパフォーマンス」といわれるMySQL互換のデータベース、Amazon Auroraを使いたかったのですがAWSの無料利用枠に含まれないため本著では断念しました。WordPressはAuroraでも動くようです。]

自力でインストールするのではなくRDSを使うことで、データのバックアップや脆弱性パッチの適用といった色々な面倒ごとをRDSにお任せできます。一方でRDSというサービス上で用意されていない機能は、たとえMySQLで実装されていても使えないため自由度は若干下がります。

旅行代理店のパック旅行を申し込めば、飛行機のチケットを取ってホテルの予約してレンタカーを借りて・・・といったこまごましたことを自分でしなくて済むから楽だけれど、代わりにできることや行けるところは限られていて自由度が下がる、というのと同じですね。

今回はWordPressと繋いで使うだけで自由度の高さは求めていないため運用コストの低いRDSを選択します。

== インスタンスを立てる事前準備

マネジメントコンソールの左上にある「サービス」から、「データベース」の下にある「RDS」（@<img>{startaws82}）をクリックしてください。

//image[startaws82][サービス＞データベース＞RDS][scale=0.8]{
//}

RDSダッシュボードを開いたら左メニューの「パラメータグループ」をクリック（@<img>{startaws83}）します。

//image[startaws83][左メニューの「パラメータグループ」をクリック][scale=0.8]{
//}

=== パラメータグループを作成

RDSでのインスタンス作成に先駆けて、パラメータグループを作成します。パラメータグループが何なのかについては追って説明しますので、とりあえず右上にある「パラメータグループの作成」をクリック（@<img>{startaws84}）してください。

//image[startaws84][「パラメータグループの作成」をクリック][scale=0.8]{
//}

パラメータグループファミリーのプルダウンから「mysql5.7」を選択して、グループ名に「start-aws-parameter-group」、説明に「Supports Japanese」と入力したら「作成」をクリック（@<img>{startaws85}）します。

//image[startaws85][「mysql5.7」を選択してグループ名と説明を入力したら「作成」をクリック][scale=0.8]{
//}

パラメータグループの一覧に、今作成した「start-aws-parameter-group」が表示されました。「start-aws-parameter-group」をクリック（@<img>{startaws86}）してください。

//image[startaws86][「start-aws-parameter-group」をクリック][scale=0.8]{
//}

すると「パラメータ」がたくさん表示（@<img>{startaws89}）されました。パラメータというのはMySQLにおけるさまざまな設定値のことです。Apacheにhttpd.confという設定ファイルがあったように、MySQLにはmy.cnfという設定ファイルがあるのですが、RDSではmy.cnfを直接書き換える代わりにこのパラメータを編集します。

//image[startaws89][「パラメータ」がたくさん表示された][scale=0.8]{
//}

先ほど作ったパラメータグループというのはこのパラメータをまとめたグループのことなのですが、この後RDSでインスタンスを作るときに「どのパラメータグループを使用するか？」という選択が出てくるため、インスタンスを作る前にパラメータグループを作っておく必要があったのです。

=== パラメータの設定

ここからは全部で8個のパラメータの値を設定していきます。似たような名前がたくさん出てきますが間違えないようにしっかりついてきてください。

先ずは「フィルタ パラメータ」と表示されているところに「character_set」と入力して検索（@<img>{startaws87}）します。検索結果が表示されたら右上にある「パラメータの編集」ボタンをクリックしてください。

//image[startaws87][「character_set」でパラメータを検索][scale=1]{
//}

そして次の5つのパラメータで値を「utf8mb4」に変更（@<img>{startaws88}）します。

 1. character_set_client
 2. character_set_connection
 3. character_set_database
 4. character_set_results
 5. character_set_server

画面上、上から4つめの「character_set_filesystem」は変更しませんので注意してください。画面には6つのパラメータが表示されていますが、utf8mb4に変更するのはそのうちの5つだけです。

//image[startaws88][5つのパラメータで値を「utf8mb4」にして「変更の保存」をクリック][scale=1]{
//}

今変更した5つのパラメータはそれぞれ次のような設定項目です。

 * character_set_client : クライアントから送られてくるSQLステートメントの文字コード
 * character_set_connection : クエリ実行時にリテラル及び数字から文字列への変換に使用される文字コード
 * character_set_database : デフォルトデータベースで使用される文字コード
 * character_set_results : クライアントへ返す実行結果やエラーメッセージで使用される文字コード
 * character_set_server : サーバのデフォルト文字コード

難しそうなことが書いてありますが、要は@<ttb>{これらのパラメータを「utf8mb4」に設定しておくと日本語や絵文字が文字化けしなくなる}という効能だけ覚えておいてください。逆に言えばこれらを設定しないとWordPressの記事で日本語や絵文字を使ったときに文字化けしてしまいます。それでは右上にある「変更の保存」をクリックしてください。

ちなみに次の2つは似たような名前なのですがこちらは何も設定しなくて大丈夫です。

 * character_set_filesystem : ファイルシステムの文字コード。デフォルト設定のままでよいため設定不要。
 * character_set_system : サーバで識別子を格納するために使用される文字コードで値は常にutf8。そもそもパラメータが存在しないため設定不要。

1～5つめの設定が済んだら今度は「collation」で検索（@<img>{startaws90}）します。検索結果が表示されたら右上にある「パラメータの編集」ボタンをクリックしてください。

//image[startaws90][「collation」でパラメータを検索][scale=0.8]{
//}

そして次の2つのパラメータで値を「utf8mb4_general_ci」に変更して、右上にある「変更の保存」をクリックしてください。

 6. collation_server（@<img>{startaws92}）
 7. collation_connection（@<img>{startaws91}）

//image[startaws92][「collation_server」の値を「utf8mb4_general_ci」にする][scale=0.8]{
//}

//image[startaws91][「collation_connection」の値も「utf8mb4_general_ci」にして「変更の保存」をクリック][scale=0.8]{
//}

今変更した2つのパラメータはそれぞれ次のような設定項目です。

 * collation_server : character_set_serverに対する照合順序
 * collation_connection : character_set_connectionに対する照合順序

7つめまでの設定が済んだら最後に「init_」で検索（@<img>{startaws93}）します。検索結果が表示されたら右上にある「パラメータの編集」ボタンをクリックしてください。

//image[startaws93][「init_」でパラメータを検索][scale=0.8]{
//}

そして次のパラメータで値に「SET NAMES utf8mb4;」と記入（@<img>{startaws94}）したら、右上にある「変更の保存」をクリックしてください。

 8. init_connect

//image[startaws94][値に「SET NAMES utf8mb4;」と記入して「変更の保存」をクリック][scale=0.8]{
//}

今変更した「init_connect」という項目は「サーバから接続元の各クライアントに対して実行される文字列」です。

8個のパラメータの値を設定したのでこれでパラメータグループの作成は完了です。続いてオプショングループも作成します。

=== オプショングループを作成

左メニューの「オプショングループ」をクリック（@<img>{startaws95}）してから、右上にある「グループの作成」をクリックします。

//image[startaws95][「オプショングループ」で「グループの作成」をクリック][scale=0.8]{
//}

名前に「start-aws-option-group」、説明に「for WordPress」と記入します。エンジンは「mysql」、メジャーエンジンのバージョンは「5.7」を選択したら「作成」をクリック（@<img>{startaws96}）します。

//image[startaws96][オプショングループの詳細を設定したら「作成」をクリック][scale=0.8]{
//}

オプショングループの一覧に「start-aws-option-group」が表示（@<img>{startaws97}）されたらオプショングループの作成は完了です。いよいよRDSでインスタンスを作りましょう。

//image[startaws97][オプショングループの一覧に「start-aws-option-group」が表示された][scale=0.8]{
//}

== RDSでインスタンスを立てよう

左メニューの「インスタンス」をクリック（@<img>{startaws98}）してから、右上にある「データベースの作成」をクリックします。

//image[startaws98][「インスタンス」で「データベースの作成」をクリック][scale=0.8]{
//}

ここから3つのステップでRDSのインスタンスを作成していきます。

=== ステップ 1:エンジンの選択

最下部にある「RDS無料利用枠の対象オプションのみを有効化」にチェック（@<img>{startaws99}）を入れて、MySQLを選択したら「次へ」をクリックします。

//image[startaws99][MySQLを選択したら「次へ」をクリック][scale=1]{
//}

=== ステップ 2:DB 詳細の指定

「インスタンスの仕様」は何も変更せず@<fn>{multiAZ}そのままで構いません。

//footnote[multiAZ][「インスタンスの仕様」に「マルチAZ配置（Multi-AZ）」という設定があります。Multi-AZとは、あらかじめメインのRDSインスタンスとは別のアベイラビリティゾーンにレプリカを待機させておいて、何らかの障害でメインのRDSインスタンスが停止してしまったら自動的に待機していたインスタンスに切り替わる仕組みです。Multi-AZはAWSの無料利用枠に含まれないため本著ではSingle-AZの構成です。]

下の方にスクロールしたら設定（@<img>{startaws100}）を次のようにします。（@<table>{db}）

//table[db][設定]{
DBインスタンス識別子	start-aws-db-instance
マスターユーザの名前	start_aws_dbuser
マスターパスワード	start_aws_db_password
パスワードの確認	マスターパスワードと同じ
//}

ここで設定した「マスターユーザの名前」と「マスターパスワード」は、この後でWordPressがデータベースに接続するときに必要となります。入力したら「次へ」をクリックします。

//image[startaws100][「設定」を入力したら「次へ」をクリック][scale=0.8]{
//}

=== ステップ 3:[詳細設定] の設定

一番上の「ネットワーク&セキュリティ」は何も変更せずそのままで構いません。その下の「データベースの設定」（@<img>{startaws101}）は次のようにします。（@<table>{dbSchema}）

//table[dbSchema][データベースの設定]{
データベースの名前	start_aws_wordpress_dbname
DBパラメータグループ	start-aws-parameter-group
オプショングループ	start-aws-option-group
//}

//image[startaws101][「データベースの設定」を入力][scale=0.8]{
//}

ここで設定した「データベースの名前」も、この後でWordPressがデータベースに接続するときに必要となります。「データベースの設定」のそれ以外の項目や、さらに下にある「暗号化」「バックアップ」「モニタリング」「ログのエクスポート」「メンテナンス」@<fn>{maintenance}はすべてデフォルトのままで構いません。

//footnote[maintenance][ちなみに「メンテナンス」で「マイナーバージョン自動アップグレード」を選択していると、新しいバージョンが出たときにMySQLを自動でアップグレードして自動で再起動してしまいます。今回は構いませんが、重要なウェブサイトやサービスで何の予告もなくデータベースに繋がらなくなったら大変ですのでこちらは基本的に無効化しておきます。]

「データベースの設定」を入力し終わったら「データベースの作成」をクリック（@<img>{startaws102}）します。

//image[startaws102][「データベースの作成」をクリック][scale=0.8]{
//}

=== セキュリティグループで3306番ポートの穴あけをしよう

「DBインスタンスを作成中です。」と表示（@<img>{startaws103}）されたら「DBインスタンスの詳細の表示」をクリックします。RDSのインスタンスができあがるまで少し時間がかかりますので、その間に「このデータベースにはどこからの接続を許可するのか？」というセキュリティグループ@<fn>{securityGroupAgain}の設定をしておきましょう。

//image[startaws103][「DBインスタンスの詳細の表示」をクリック][scale=0.8]{
//}

//footnote[securityGroupAgain][何度か出てきていますがセキュリティグループはいわゆる「ファイアウォール」のことです。セキュリティグループってどんなものだったっけ？という方は@<chapref>{serverBuilding}でEC2のインスタンスを作るとき「ステップ6」で設定したことを思い出してください。]

今作った「start-aws-db-instance」というRDSインスタンスの詳細が表示（@<img>{startaws104}）されます。

//image[startaws104][「start-aws-db-instance」というRDSインスタンスの詳細][scale=0.8]{
//}

下の方にスクロールして「設定」（@<img>{startaws105}）を見てください。RDSインスタンスの手前に立ちはだかっているのは「rds-launch-wizard」という名前のセキュリティグループです。「rds-launch-wizard」をクリックしてください。

//image[startaws105][セキュリティグループの「rds-launch-wizard」をクリック][scale=0.8]{
//}

「rds-launch-wizard」の「インバウンド」タブで「編集」をクリック（@<img>{startaws106}）します。

//image[startaws106][「インバウンド」タブで「編集」をクリック][scale=0.8]{
//}

データベースに記事データを保存したり、データベースへ記事データを取りに行ったりするのはEC2のインスタンス上で動いているWordPressですので、このセキュリティグループではEC2のインスタンスからRDSの「MySQL（ポート番号3306番）」へ通信できるように許可する設定をしてやらなければいけません。

ソースに書かれたIPアドレスを消して「ec2」と入力（@<img>{startaws107}）すると下に「ec2-security-group」が表示されますのでクリックしてください。

//image[startaws107][「ec2」と入力して「ec2-security-group」が表示されたらクリック][scale=0.8]{
//}

ソースに「sg-0e0e65673a262e18f」のようなEC2のセキュリティグループIDが表示（@<img>{startaws108}）されたら「保存」をクリックします。

//image[startaws108][「保存」をクリック][scale=0.8]{
//}

これでEC2のインスタンスからRDSのインスタンスの「MySQL（ポート番号3306番）」へ接続できるようになりました。

=== エンドポイントのドメイン名をメモしておこう

そろそろRDSのインスタンスができあがっている頃です。マネジメントコンソールの左上にある「サービス」から、「データベース」の下にある「RDS」（@<img>{startaws109}）をクリックしてください。

//image[startaws109][サービス＞データベース＞RDS][scale=0.8]{
//}

RDSダッシュボードを開いたら左メニューの「インスタンス」をクリック（@<img>{startaws110}）します。「start-aws-db-instance」というインスタンスのステータスが「利用可能」になっていたら「start-aws-db-instance」をクリックしてください。

//image[startaws110][左メニューの「インスタンス」＞「start-aws-db-instance」をクリック][scale=0.8]{
//}

下の方にスクロールすると「接続」のところに「エンドポイント」（@<img>{startaws111}）があります。この「start-aws-db-instance.cyjoha27mqmm.ap-northeast-1.rds.amazonaws.com」という「エンドポイント」は、後でWordPressからデータベースに接続するときに必要となります。長いのでパソコンのメモ帳にしっかりコピーペーストしておいてください。

//image[startaws111][「エンドポイント」をしっかりメモしておこう][scale=0.8]{
//}

=== ウェブサーバから接続確認してみよう

それではEC2のインスタンスからRDSのMySQLに接続できるか、mysqlコマンドを使って試してみましょう。いわゆる「ウェブサーバからデータベースへの疎通確認」ですね。MySQLに接続するときは先ほどメモしておいた

 * エンドポイント
 * マスターユーザの名前
 * マスターパスワード

の3つを使用します。

Windowsの方はRLoginを起動して「start-aws-instance」に接続してください。Macの方はターミナルで次のコマンドを実行してください。

//cmd{
ssh ec2-user@login.自分のドメイン名 -i ~/Desktop/start-aws-keypair.pem
//}

「Amazon Linux AMI」と表示されたら次のコマンドを叩きます。

//cmd{
$ mysql -h エンドポイント -u マスターユーザの名前 -p
//}

-hオプションは「接続先ホスト」を指定しています。-uオプションは「このユーザで」、-pオプションは「パスワード認証で」という意味です。筆者だったらこんなコマンドになります。

//cmd{
$ mysql -h start-aws-db-instance.cyjoha27mqmm.ap-northeast-1.rds.amazonaws.com
        -u start_aws_dbuser -p
※実際は改行せずに1行で実行
//}

コマンドを叩くと次のように表示されます。

//cmd{
Enter password:
//}

パスワードを求められているので「マスターパスワード」の「start_aws_db_password」を入力してEnterキーを押します。なお@<ttb>{パスワードは入力しても画面上何の変化もありません}。カーソルの位置も変わらないし「***」のような表示も一切されません。入力できている手ごたえがまったくありませんがちゃんと入力できていますし、間違えたときはBackSpaceキーを押せば消せていますので大丈夫です。パスワードを入力したらEnterキーを押してください。

パスワードを入力後、次のように一番下に「mysql> 」と表示されたらMySQLへのログインに成功しています。

//cmd{
$ mysql -h エンドポイント -u マスターユーザの名前 -p
Enter password: 
Welcome to the MySQL monitor.  Commands end with ; or \g.
Your MySQL connection id is 25
Server version: 5.7.22-log Source distribution

Copyright (c) 2000, 2018, Oracle and/or its affiliates. All rights reserved.

Oracle is a registered trademark of Oracle Corporation and/or its
affiliates. Other names may be trademarks of their respective
owners.

Type 'help;' or '\h' for help. Type '\c' to clear the current input statement.

mysql> 
//}

試しに「show databases;」と入力してEnterキーを押すとデータベースの一覧が表示されます。ちゃんと「start_aws_wordpress_dbname」という名前のデータベースも作成されていることが確認できました。

//cmd{
mysql> show databases;
+----------------------------+
| Database                   |
+----------------------------+
| information_schema         |
| innodb                     |
| mysql                      |
| performance_schema         |
| start_aws_wordpress_dbname |
| sys                        |
+----------------------------+
6 rows in set (0.00 sec)
//}

それではMySQLを抜けてEC2のインスタンスに戻りたいので「exit」と入力してEnterキーを押してください。

//cmd{
mysql> exit
Bye
//}

Byeと表示されたらMySQLとの接続を切ってEC2のインスタンスへ戻ってこられています。

これでデータベースサーバは用意できました。いよいよWordPressのインストールを行いましょう。