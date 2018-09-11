= WordPressでサイトを作ろう

この章ではWordPressをインストールしてウェブサイトを作ります。
大変な道のりでしたがいよいよおしゃれなサイトがお目見えです！

//pagebreak

== WordPressのインストール

これからEC2のインスタンスでWordPressのインストールを行います。Windowsの方はRLoginを起動して「start-aws-instance」に接続してください。Macの方はターミナルで次のコマンドを実行してください。

//cmd{
ssh ec2-user@login.自分のドメイン名 -i ~/Desktop/start-aws-keypair.pem
//}

「Amazon Linux AMI」と表示されたらログイン完了です。ここからの作業はrootにならずに@<ttb>{ec2-userのまま}で行ってください。

=== WordPressをダウンロード

先ずはcurlコマンドを使って最新のWordPress（@<href>{https://wordpress.org/latest.tar.gz}）をダウンロードしましょう。curlコマンドは何もオプションをつけないと結果をそのまま画面に出力しますが、-Oオプションを付けるとファイルとして保存してくれます。

//cmd{
$ curl -O https://wordpress.org/latest.tar.gz
  % Total    % Received % Xferd  Average Speed   Time    Time     Time  Current
                                 Dload  Upload   Total   Spent    Left  Speed
100 8538k  100 8538k    0     0  3342k      0  0:00:02  0:00:02 --:--:-- 3342k
//}

ダウンロードしたファイルをlsコマンドで確認してみましょう。

//cmd{
$ ls -lh /home/ec2-user/
合計 8.4M
-rw-rw-r-- 1 ec2-user ec2-user 8.4M  9月  5 21:08 latest.tar.gz
//}

圧縮された最新版のWordPress（latest.tar.gz）をダウンロードできました。

=== 展開してドキュメントルートに設置

実はWordPressのインストールと言っても、今ダウンロードした圧縮ファイルを展開してドキュメントルートに置き、後はブラウザでぽちぽちと進めていくだけなので簡単です。

それでは圧縮・解凍ソフトのようなtarコマンドを使ってWordPressの圧縮ファイル（latest.tar.gz）を展開します。lsコマンドで確認すると、展開によってwordpressというディレクトリができていることがわかります。

//cmd{
$ tar -xzf /home/ec2-user/latest.tar.gz

$ ls -lh /home/ec2-user/
合計 8.4M
-rw-rw-r-- 1 ec2-user ec2-user 8.4M  9月  5 21:08 latest.tar.gz
drwxr-xr-x 5 ec2-user ec2-user 4.0K  8月  3 05:39 wordpress
//}

展開できたらmvコマンド@<fn>{mv}を使ってwordpressディレクトリの中身をすべてドキュメントルートに移動させましょう。特にいちばん後ろのスラッシュは書き忘れないように注意してください。

//footnote[mv][mvはmoveの略。ファイルを移動させたりファイル名を変更したりできるコマンドです。]

//cmd{
$ sudo mv /home/ec2-user/wordpress/* /var/www/start-aws-documentroot/
//}

今後、WordPressの管理画面から画像ファイルをアップしたりプラグイン@<fn>{plugin}をインストールしたりするためには、ドキュメントルート以下のファイルやディレクトリに対してapacheユーザが権限を持っていないといけません。chownコマンド@<fn>{chown}でドキュメントルート以下のオーナー（持ち主）をapacheユーザに変更しておきましょう。

//footnote[plugin][WordPressの拡張機能のこと。]
//footnote[chown][chownはchange ownershipの略。]

//cmd{
$ sudo chown apache:apache -R /var/www/start-aws-documentroot

$ ls -ld /var/www/start-aws-documentroot
drwxr-xr-x 6 apache apache 4096  9月  5 22:04 /var/www/start-aws-documentroot
//}

それから@<chapref>{apacheSetting}で動作確認用に作った「AWSをはじめよう」と書いてあるindex.htmlファイルは削除しておきましょう。

//cmd{
$ sudo rm -f chown /var/www/start-aws-documentroot/index.html
//}

これでドキュメントルート以下にあるのは展開したWordPressのファイルだけになりました。

//cmd{
$ ls -lh /var/www/start-aws-documentroot/
合計 196K
-rw-r--r--  1 apache apache  418  9月 25  2013 index.php
-rw-r--r--  1 apache apache  20K  1月  7  2018 license.txt
-rw-r--r--  1 apache apache 7.3K  3月 19 01:13 readme.html
drwxr-xr-x  5 apache apache 4.0K  8月  3 05:39 wordpress
-rw-r--r--  1 apache apache 5.4K  5月  2 07:10 wp-activate.php
drwxr-xr-x  9 apache apache 4.0K  8月  3 05:39 wp-admin
-rw-r--r--  1 apache apache  364 12月 19  2015 wp-blog-header.php
-rw-r--r--  1 apache apache 1.9K  5月  3 07:11 wp-comments-post.php
-rw-r--r--  1 apache apache 2.8K 12月 16  2015 wp-config-sample.php
drwxr-xr-x  4 apache apache 4.0K  8月  3 05:39 wp-content
-rw-r--r--  1 apache apache 3.6K  8月 20  2017 wp-cron.php
drwxr-xr-x 18 apache apache  12K  8月  3 05:39 wp-includes
-rw-r--r--  1 apache apache 2.4K 11月 21  2016 wp-links-opml.php
-rw-r--r--  1 apache apache 3.3K  8月 22  2017 wp-load.php
-rw-r--r--  1 apache apache  37K  7月 16 23:14 wp-login.php
-rw-r--r--  1 apache apache 7.9K  1月 11  2017 wp-mail.php
-rw-r--r--  1 apache apache  16K 10月  4  2017 wp-settings.php
-rw-r--r--  1 apache apache  30K  4月 30 08:10 wp-signup.php
-rw-r--r--  1 apache apache 4.6K 10月 24  2017 wp-trackback.php
-rw-r--r--  1 apache apache 3.0K  9月  1  2016 xmlrpc.php
//}

=== サイトにアクセスしてインストール実行

それではブラウザで@<href>{http://www.自分のドメイン/}を開いてください。筆者なら自分のドメインは「startdns.fun」なので@<href>{http://www.startdns.fun/}を開きます。

するとWordPressの言語選択画面（@<img>{startaws112}）が表示されるので「日本語」を選択して「続ける」をクリックします。

//image[startaws112][「日本語」を選択して「続ける」をクリック][scale=0.8]{
//}

続いて「WordPressへようこそ。」という画面（@<img>{startaws113}）が表示されたら「さあ、始めましょう！」をクリックします。

//image[startaws113][「さあ、始めましょう！」をクリック][scale=0.8]{
//}

データベースの接続情報を入力する画面（@<img>{startaws114}）が表示されたら、@<chapref>{database}で設定した内容を思い出しながら次のように入力します。（@<table>{dbAuth}）テーブル接頭辞は変更せずそのままで構いません。

//table[dbAuth][データベースの接続情報]{
データベース名	start_aws_wordpress_dbname（データベースの名前）
ユーザー名	start_aws_dbuser（マスターユーザの名前）
パスワード	start_aws_db_password（マスターパスワード）
データベースのホスト名	エンドポイント
//}

エンドポイントは「start-aws-db-instance.cyjoha27mqmm.ap-northeast-1.rds.amazonaws.com」のような長いドメイン名です。パソコンのメモ帳にメモしてあると思いますので、そこからコピーペーストしましょう。すべて入力したら「送信」をクリックします。

//image[startaws114][データベースの接続情報を入力して「送信」をクリック][scale=0.8]{
//}

データベースの接続情報に誤りがなく、WordPressがデータベースと繋がったら「この部分のインストールは無事完了しました。WordPress は現在データベースと通信できる状態にあります。」と表示（@<img>{startaws115}）されます。「インストール実行」をクリックしましょう。

//image[startaws115][「インストール実行」をクリック][scale=0.8]{
//}

「WordPressの有名な5分間インストールプロセスへようこそ!」と表示（@<img>{startaws116}）されたら、サイトのタイトルなどを入力します。サイトのタイトルは好きなものにしてください。ユーザー名やパスワードはWordPressの管理画面にログインするときに使用しますのであなた自身で決めてメモ（@<table>{wpAdminMemo}）しておいてください。「検索エンジンでの表示」はどちらでも構いませんが、作ったサイトをGoogleなどの検索結果に表示したくなければチェックを入れておきましょう。もしパスワードを忘れてしまった場合、ここに書いたメールアドレス宛てにパスワードリセットのメールが届きますのでメールアドレスは正確に入力してください。すべて入力したら「WordPressをインストール」をクリックします。

//table[wpAdminMemo][WordPress管理画面に入るための情報をメモ]{
------------------------------------
ユーザー名	　　　　　　　　　　　　　　　　　　　　
パスワード	　　　　　　　　　　　　　　　　　　　　
メールアドレス	　　　　　　　　　　　　　　　　　　　　
//}

//image[startaws116][「WordPressをインストール」をクリック][scale=0.8]{
//}

「成功しました!」と表示（@<img>{startaws117}）されたらWordPressのインストールは完了です。「ログイン」をクリックしてWordPressの管理画面に入ってみましょう。

//image[startaws117][「ログイン」をクリックしてWordPressの管理画面に入ってみよう][scale=0.8]{
//}

== 管理画面にログイン

WordPressの管理画面に入るため、先ほど設定したユーザー名とパスワードを入力（@<img>{startaws118}）したら「ログイン状態を保存する」にチェックを入れて「ログイン」をクリックします。

//image[startaws118][ユーザー名とパスワードを入力して「ログイン」をクリック][scale=0.8]{
//}

もし左メニューで「更新」に赤いマーク（@<img>{startaws119}）がついていたら、クリックしてWordPress本体やプラグインの更新をしておきましょう。

//image[startaws119][「更新」に赤いマークがついていたら「更新」をクリック][scale=0.8]{
//}

「WordPress の新しいバージョンがあります。」と表示されていますので「今すぐ更新」をクリック（@<img>{startaws120}）します。@<fn>{security}

//footnote[security][WordPressでは定期的に脆弱性が発見されて対策済みのバージョンが公開されます。脆弱性（ぜいじゃくせい）というのは悪用が可能なバグや設定不備のことです。もしWordPressに脆弱性が見つかって対策済みの新しいバージョンのWordPressが公開されたとしても、あなたが更新をしないとウェブサイトは脆弱性がある危険な状態のままで放置されていることになります。古いバージョンのWordPressを使っているとサイトを改ざんしてウイルスをばらまかれたりデータベースの個人情報を盗まれたりする可能性もありますので、新しいバージョンが出たらきちんと更新しましょう。]

//image[startaws120][「今すぐ更新」をクリック][scale=0.8]{
//}

「今すぐ更新」をクリックすると更新の進捗が表示（@<img>{startaws121}）され、更新完了すると新しいバージョンではどんな修正がされたのか？が表示されます。それではできあがったおしゃれなサイトを見てみましょう。左上の家のマークをクリック（@<img>{startaws122}）してください。

//image[startaws121][更新の進捗が表示される][scale=0.8]{
//}

//image[startaws122][更新完了したら家のマークをクリック][scale=0.8]{
//}

そしてこちらが完成したWordPressのおしゃれなサイトです！（@<img>{startaws123}）ここからは見た目をカスタマイズするもよし、技術的なことを調べたブログ記事を日々綴っていくもよし、自分のサイトを自由に楽しんでください。

//image[startaws123][できあがった「自分のサイト」をここからは自由にカスタマイズしよう][scale=0.8]{
//}

=== 【ドリル】WordPressからのメールが迷惑メール扱いされてしまう

==== 問題

「AWSをはじめよう」を読みながら構築した環境で、WordPressの管理画面に入るパスワードを忘れてしまったためパスワードのリセットを行いました。ところがいくら待ってもメールが届きません。確認したところパスワードリセットのメール（@<img>{startaws206}）は迷惑メールのトレイに入っていました。

//image[startaws206][パスワードリセットのメールが迷惑メール扱いされていた][scale=0.6]{
//}

原因は「SPFが設定されていないこと」のようです。送信元のメールアドレスは「WordPress <wordpress@startdns.fun>」でした。このとき次のどれを設定すれば迷惑メール扱いされなくなるでしょうか？

 * A. startdns.funのTXTレコードに「"v=spf1 ip4:xxx.xxx.xxx.xxx ~all"」のようにElastic IPのアドレスを設定する
 * B. www.startdns.funのTXTレコードに「"v=spf1 ip4:xxx.xxx.xxx.xxx ~all"」のようにElastic IPのアドレスを設定する
 * C. startdns.funのTXTレコードに「"v=spf1 a:login.startdns.fun ~all"」のようにSSHログインで使っているドメイン名を設定する

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はAまたはCです。SPFレコードを設定すべきなのは送信元のメールアドレスで使われているドメイン名です。EC2のインスタンスからメールが送信されるとき送信元のIPアドレスはElastic IPとなります。Aのように直接Elastic IPのIPアドレスを指定してもいいですし、CのようにElastic IPと紐づいているドメイン名を指定しても構いません。

CのようにしておくとElastic IPが変更になったときに「login.startdns.fun」のAレコードだけを変更すればいいため変更箇所が少なくて済みます。

//image[startaws207][筆者はCの方法でSPFレコードを設定しました][scale=0.8]{
//}

=== 管理画面にダイジェスト認証をかけよう

ところでWordPressは利用者が多いため、その管理画面を乗っ取ろうと狙ってくる攻撃も多いです。「こんな作ったばかりの小さなブログに攻撃なんか来ないのでは？」と思われるかもしれませんが、攻撃者はIPアドレスを端から順番に試していくだけなので、サイトの開設時期や規模にかかわらずどんなサーバでも攻撃はされると思って間違いありません。

管理画面にログインするにはユーザー名とパスワードの認証が必要ですが、安全のためその手前にもうひとつ「ダイジェスト認証」という認証をかけておきましょう。

EC2のインスタンスでコマンドを叩きますのでRLoginやターミナルに戻ってrootになってください。

//cmd{
$ sudo su -
//}

rootになったら先ずはhtdigestコマンドを使ってダイジェスト認証のパスワードファイルを作成します。

//cmd{
# htdigest -c /etc/httpd/conf/htdigest wp-admin-area start-aws-digest-user
//}

「New password:」と表示されたら「start-aws-digest-password」と入力してEnterキーを押してください。再度「Re-type new password:」とパスワードを求められますので、もう一度「start-aws-digest-password」と入力してEnterキーを押します。

//cmd{
New password:
Re-type new password:
//}

これでダイジェスト認証のパスワードファイルが生成できました。catコマンドでパスワードファイルを見てみましょう。

//cmd{
# cat /etc/httpd/conf/htdigest
start-aws-digest-user:wp-admin-area:10b74c85e2a0273d00eee83755e329b8
//}

続いてviコマンドでバーチャルホストにダイジェスト認証の設定を書き足します。

//cmd{
# vi /etc/httpd/conf.d/start-aws-virtualhost.conf 
//}

i（アイ）を押して「編集モード」になったら、次のようになダイジェスト認証の設定をVirtualHostディレクティブの中に追記します。

//cmd{
<Directory "/var/www/start-aws-documentroot/wp-admin">
    AuthType Digest
    AuthName wp-admin-area
    AuthUserFile /etc/httpd/conf/htdigest
    Require valid-user
</Directory>
//}

書き終わったらESCキーを押して「閲覧モード」に戻り、「:wq」と入力してEnterキーを押せば保存されます。保存できたら確認のためcatコマンドを叩いてダイジェスト認証の設定が追加されているか確認してください。

//cmd{
# cat /etc/httpd/conf.d/start-aws-virtualhost.conf
<VirtualHost *:80>
    DocumentRoot "/var/www/start-aws-documentroot"
    ServerName www.startdns.fun

    ErrorLog "logs/start-aws-error.log"
    CustomLog "logs/start-aws-access.log" combined

    <Directory "/var/www/start-aws-documentroot">
        AllowOverride All
    </Directory>

    <Directory "/var/www/start-aws-documentroot/wp-admin">
        AuthType Digest
        AuthName wp-admin-area
        AuthUserFile /etc/httpd/conf/htdigest
        Require valid-user
    </Directory>
</VirtualHost>
//}

apachectlで構文チェックをしてみましょう。「Syntax OK」とだけ表示されれば問題ありません。

//cmd{
# apachectl configtest
Syntax OK
//}

それではダイジェスト認証の設定を有効にするため、apachectlでApacheを再起動しましょう。

//cmd{
# apachectl restart
//}

何のメッセージも表示されなければ問題なくApacheが再起動できています。それではブラウザで確認してみましょう。

先ずは管理画面ではなくブログの方を表示してみましょう。ブラウザで@<href>{http://www.自分のドメイン/}を開いてください。こちらは先ほどまでと代わらず普通に表示（@<img>{startaws126}）されるはずです。

//image[startaws126][ブログは認証なしで普通に表示される][scale=0.8]{
//}

続いてブラウザでWordPressの管理画面（@<href>{http://www.自分のドメイン/wp-admin/}）を開いてみましょう。すると「ユーザー名とパスワードを入力してください」というダイジェスト認証のポップアップが表示（@<img>{startaws125}）されますので、先ほど設定したダイジェスト認証のユーザー名とパスワードを入力して「OK」をクリックしてください。（@<table>{digestAuth}）

//image[startaws125][管理画面では「ユーザー名とパスワードを入力してください」というダイジェスト認証のポップアップが表示された][scale=0.8]{
//}

//table[digestAuth][ダイジェスト認証の情報]{
------------------------------------
ユーザー名	start-aws-digest-user
パスワード	start-aws-digest-password
//}

正しいユーザー名とパスワードを入れれば管理画面に入るためのログイン画面（もしくは管理画面）が表示（@<img>{startaws127}）されますが、間違ったものを入力すると「Unauthorized」と表示（@<img>{startaws128}）されて管理画面には入れません。これで管理画面は「ダイジェスト認証」と「WordPressの認証」の2段階@<fn>{3rdAuth}で守られるようになりました。

//image[startaws128][正しいユーザー名とパスワードを入れないと「Unauthorized」と表示されて管理画面に入れない][scale=0.8]{
//}

//image[startaws127][管理画面が「ダイジェスト認証」と「WordPressの認証」の2段階で守られるようになった][scale=0.8]{
//}

//footnote[3rdAuth][自宅のIPアドレスが固定の人はIP認証もかけておくとさらに安心です。]

== 画像をS3に保存する

ところでWordPressで画像をアップすると、画像ファイルはドキュメントルート以下にある「wp-content/uploads」というディレクトリに保存されます。

//cmd{
/var/www/start-aws-documentroot/wp-content/uploads/
//}

ですが画像をEC2インスタンス内に直接保存することによって、次のようなデメリットが発生します。

 1. アクセス数が増えてきて負荷分散のためウェブサーバの台数を増やしたときに画像が片方のサーバにしか保存されず、もう1台のサーバでは記事内の画像が表示されなくなってしまう
 2. ウェブサーバが壊れてAMI@<fn>{ami}から復元したとき、画像のフォルダがAMIを作った時点まで先祖返りしてしまい、記事内の画像が表示されなくなってしまう

//footnote[ami][AMIについては@<chapref>{backup}で解説します。]

そこで台数を増やしたりサーバを復元したりしたときでも記事内の画像が問題なく表示されるよう、WordPressでアップした画像はインスタンス内に保存するのではなくAmazon S3に保存するようにしておきましょう。

=== Amazon S3とは？

Amazon S3というのは「Amazon Simple Storage Service」の略で、頭文字のSが3つなのでS3です。シンプルストレージという名前のとおり、S3はDropboxやGoogleクラウドのようにファイルを保存しておけるサービスです。S3は99.999999999%@<fn>{nine}の耐久性をもち、格納できるデータの容量も無制限ですので「ハードディスクが壊れて保存してた画像が全部消えちゃった・・・」「容量がいっぱいになっちゃってこれ以上保存できない！」といったトラブルとも無縁です。

//footnote[nine][イレブンナインと読みます。格好いい・・・！]

S3に保存した画像ファイルにはすべてURLが付与され、HTTPSでどこからでもアクセスができます。

=== S3アップ用のIAMユーザーを作ろう

皆さんがマネジメントコンソールにログインするときに使っている「start-aws-user」というIAMユーザーは「AdministratorAccess」という一番強い権限を持っています。このIAMユーザーをそのままWordPressに使わせるのは危険ですので「IAMユーザーには必要最小限の権限だけを付与すべき」という原則にしたがって、S3にファイルを保存するためだけのIAMユーザーを作成しましょう。

WordPressでアップしたファイルをS3に保存するため、先ずはIAMのアクセスキーを発行します。細かな手順は省略@<fn>{iamAgain}しますが、マネジメントコンソールでIAMダッシュボードを開いて次のような流れでS3アップ専用のIAMユーザーを作成してください。

 1. s3-upload-groupというIAMグループを作る
 2. s3-upload-groupにAmazonS3FullAccessというポリシーをアタッチする
 3. s3-upload-userというIAMユーザを作って「アクセスの種類」を「プログラムによるアクセス」にする
 4. s3-upload-userをs3-upload-groupに追加する

//footnote[iamAgain][@<chapref>{doTheFirst}でIAMグループとIAMユーザーを作ってポリシーをアタッチしたときとほぼ同じ手順ですのでそちらを参照してください。大きく異なるのはIAMユーザーの「アクセスの種類」が「AWSマネジメントコンソールへのアクセス」ではなく「プログラムによるアクセス」になっている点です。マネジメントコンソールにログインして操作するのではなく、WordPressのプログラムからS3を利用したいので「プログラムによるアクセス」を選択しています。]

S3アップ専用のIAMユーザが作成（@<img>{startaws147}）できたら、アクセスキーIDとシークレットアクセスキーをパソコンのメモ帳にメモ@<fn>{keyOnce}しておいてください。

//footnote[keyOnce][シークレットアクセスキーが表示されるのはこの1回きりで以降は絶対に表示されません。もしシークレットアクセスキーをメモし忘れた場合は、いったんアクセスキーを削除して作成しなおしてください。IAMダッシュボードから左メニューの「ユーザー」を開いて、「s3-upload-user」をクリックすると「認証情報」タブの中でアクセスキーの削除や作成ができます。]

//image[startaws147][「アクセスキーID」と「シークレットアクセスキー」をメモしておこう][scale=1]{
//}

この2つはとても大切なものです。他の人に知られるとS3へ無断でファイルをアップされたり、S3にアップしたファイルを消されたりしてしまいますので、@<ttb>{アクセスキーIDとシークレットアクセスキーは外部へ絶対に漏らさない}@<fn>{aKey}ようにしてください。ソースコードに直接書いてそれをGitHubの公開リポジトリへプッシュしてしまう、というのがありがちな失敗です。

//footnote[aKey][筆者は堂々と本著に載せていますが、勿論このアクセスキーはすでに無効にしてありますのでご安心ください。]

S3アップ専用のIAMユーザが作成できたら、WordPressプラグインのインストールに進みましょう。

=== WordPressにS3を使うためのプラグインを入れよう

WordPressのプラグイン（拡張機能）を使って、記事の画像をS3に保存する設定を行います。使用するプラグインは次の2つです。

 1. Amazon Web Servicesプラグイン
 2. WP Offload S3 Liteプラグイン

==== Amazon Web Servicesプラグイン

「プラグイン」の「新規追加」をクリック（@<img>{startaws144}）して、「プラグインの検索...」と書かれたところに「Amazon Web Services」と入力します。「Amazon Web Services」が表示されたら「今すぐインストール」をクリックします。

//image[startaws144][「Amazon Web Services」を検索して「今すぐインストール」をクリック][scale=0.8]{
//}

ボタンの表示が「インストール中」の後に「有効化」になったらクリック（@<img>{startaws145}）します。

//image[startaws145][「有効化」になったらクリック][scale=0.8]{
//}

Amazon Web Servicesプラグインがインストールできたので「Access Keys」をクリック（@<img>{startaws146}）します。

//image[startaws146][Amazon Web Servicesプラグインの「Access Keys」をクリック][scale=0.8]{
//}

「click here to reveal a form.」をクリックして、先ほど作ったS3アップ専用のIAMユーザである「s3-upload-user」のアクセスキーIDとシークレットアクセスキーを入力します。どちらも入力できたら「Save Changes」をクリックします。

//image[startaws148][アクセスキーIDとシークレットアクセスキーを入力したら「Save Changes」をクリック][scale=0.8]{
//}

「Settings saved.」と表示されたらAmazon Web Servicesプラグインの設定は完了です。

==== WP Offload S3 Liteプラグイン

「プラグイン」の「新規追加」をクリック（@<img>{startaws149}）して、「プラグインの検索...」と書かれたところに「WP Offload S3 Lite」と入力します。「WP Offload S3 Lite」が表示されたら「今すぐインストール」をクリックします。

//image[startaws149][「WP Offload S3 Lite」を検索して「今すぐインストール」をクリック][scale=0.8]{
//}

ボタンの表示が「インストール中」の後に「有効化」になったらクリック（@<img>{startaws150}）します。

//image[startaws150][「有効化」になったらクリック][scale=0.8]{
//}

WP Offload S3 Liteプラグインがインストールできたので「Settings」をクリック（@<img>{startaws151}）します。

//image[startaws151][WP Offload S3 Liteプラグインの「Settings」をクリック][scale=0.8]{
//}

WordPressでアップした画像を保存しておくための「バケット」と呼ばれる入れ物がS3にまだないので「Create new bucket」をクリック（@<img>{startaws152}）します。

//image[startaws152][バケットがまだないので「Create new bucket」をクリック][scale=0.8]{
//}

「Bucket Name」に「start-aws-wordpress-bucket」と入力（@<img>{startaws153}）し、「Region」は「Asia Pacific (Tokyo)」を選択したら「Create new bucket」をクリックします。

//image[startaws153][バケットの名前とリージョンを入れて「Create new bucket」をクリック][scale=0.8]{
//}

「設定を保存しました。」と表示（@<img>{startaws154}）されました。これでバケットの作成が完了して画像がS3へ保存されるようになりました。

//image[startaws154][バケットの作成が完了して画像がS3へ保存されるようになった][scale=0.8]{
//}

下にスクロールして「Force HTTPS」をオン（@<img>{startaws155}）にしたら「Save Changes」をクリックします。@<fn>{https}

//footnote[https][デフォルトだと「ページをHTTPで開いたら画像もHTTPで表示、ページをHTTPSで開いたら画像もHTTPで表示」という設定なのですが、「Force HTTPS」をオンにしておくと「画像は常にHTTPSで表示」になります。今後サイトをHTTPS化したときに画像のURLをHTTPからHTTPSへ書き換えなくて済むようオンにしておくことをお勧めします。]	

//image[startaws155][画像は常にHTTPSで表示されるよう「Force HTTPS」をオンにして「Save Changes」をクリック][scale=0.8]{
//}

「設定を保存しました。」と表示されたらWP Offload S3 Liteプラグインの設定は完了@<fn>{cloudFront}です。

//footnote[cloudFront][ちなみにWP Offload S3 LiteプラグインではS3ではなくCloudFront（クラウドフロント）を使う設定にもできるようです。本著では扱いませんがCloudFrontはCDN（Content Delivery Network）のサービスです。CloudFrontを使うと画像や動画などのコンテンツを世界中のCDNサーバを使って配信できるため、ウェブサイトが高速で表示されるようになります。]

=== 投稿を試してみよう

画像をS3にアップする設定がされたか、試しに記事を投稿してみましょう。

左メニューの「投稿」から「新規追加」をクリック（@<img>{startaws156}）したら、タイトルに「画像はS3にアップされるようになりました」と入力します。タイトルが入力できたら「メディアを追加」をクリックしてください。

//image[startaws156][タイトルを入力したら「メディアを追加」をクリック][scale=0.8]{
//}

「ファイルを選択」をクリック（@<img>{startaws157}）して適当な画像を選択したら「投稿に挿入」をクリックします。

//image[startaws157][適当な画像を選択したら「投稿に挿入」をクリック][scale=0.8]{
//}

「公開」をクリック（@<img>{startaws158}）します。

//image[startaws158][「公開」をクリック][scale=0.8]{
//}

投稿が公開されたら「投稿を表示」をクリック（@<img>{startaws159}）してください。

//image[startaws159][「投稿を表示」をクリック][scale=0.8]{
//}

記事を確認したら画像を右クリックして「画像だけを表示」をクリック（@<img>{startaws160}）します。

//image[startaws160][画像を右クリックして「画像だけを表示」をクリック][scale=0.8]{
//}

すると画像のURLが「@<href>{https://s3-ap-northeast-1.amazonaws.com/start-aws-wordpress-bucket/wp-content/uploads/2018/09/07182149/circle_cut_color.png}」のようになっている（@<img>{startaws161}）ので、WordPressでアップした画像がS3に保存されて記事に挿入されていることが分かります。

//image[startaws161][画像のURLがS3になっている][scale=0.8]{
//}

以上でWordPressのインストールと設定は完了です。お疲れさまでした！