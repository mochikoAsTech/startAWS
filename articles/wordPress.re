= WordPressでサイトを作ろう

この章ではWordPressをインストールしてウェブサイトを作ります。
大変な道のりでしたがいよいよおしゃれなサイトがお目見えですよ！

//pagebreak

== WordPressのインストール

これからEC2のインスタンスでWordPressのインストールを行います。Windowsの方はRLoginを起動して「start-aws-instance」に接続してください。Macの方はターミナルで次のコマンドを実行してください。

//cmd{
ssh ec2-user@login.自分のドメイン名 -i ~/Desktop/start-aws-keypair.pem
//}

「Amazon Linux AMI」と表示されたらログイン完了です。ここからの作業はrootにならずにec2-userのままで行ってください。

=== WordPressをダウンロード

先ずはcurlコマンドを使って最新のWordPressをダウンロードしましょう。curlコマンドは何もオプションをつけないと結果をそのまま画面に出力しますが、-Oオプションを付けるとファイルとして保存してくれます。

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

=== インストールは展開するだけ

実はWordPressのインストールと言っても、先ほどダウンロードしてきた圧縮ファイルをドキュメントルートで展開して、後はブラウザでぽちぽちと進めていくだけなので簡単です。

それではtarコマンドを使ってWordPressの圧縮ファイル（latest.tar.gz）を展開します。lsコマンドで確認すると、展開によってwordpressというディレクトリができていることがわかります。

//cmd{
$ tar -xzf /home/ec2-user/latest.tar.gz

$ ls -lh /home/ec2-user/
合計 8.4M
-rw-rw-r-- 1 ec2-user ec2-user 8.4M  9月  5 21:08 latest.tar.gz
drwxr-xr-x 5 ec2-user ec2-user 4.0K  8月  3 05:39 wordpress
//}

展開できたらwordpressディレクトリの中身をすべてドキュメントルートに移動させましょう。特にいちばん後ろのスラッシュは書き忘れないように注意してください。

//cmd{
$ sudo mv wordpress/* /var/www/start-aws-documentroot/
//}

今後、WordPressの管理画面から画像ファイルをアップしたり、プラグインをインストールしたりするためには、ドキュメントルート以下のファイルやディレクトリに対してapacheユーザが権限を持っていないといけません。chownコマンド@<fn>{chown}でドキュメントルート以下のオーナー（持ち主）をapacheユーザに変更しておきましょう。

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

それではブラウザで@<href>{http://www.自分のドメイン/}を開きます。筆者なら自分のドメインは「startdns.fun」なので@<href>{http://www.startdns.fun/}です。

するとWordPressの言語選択画面（@<img>{startaws112}）が表示されるので「日本語」を選択して「続ける」をクリックします。

//image[startaws112][「日本語」を選択して「続ける」をクリック][scale=0.8]{
//}

続いて「WordPressへようこそ。」という画面（@<img>{startaws113}）が表示されたら「さあ、始めましょう！」をクリックします。

//image[startaws113][「さあ、始めましょう！」をクリック][scale=0.8]{
//}

データベースの接続情報を入力する画面（@<img>{startaws114}）が表示されたら、@<chapref>{database}で設定した内容を思い出して次のように入力します。（@<table>{dbAuth}）テーブル接頭辞は変更せずそのままで構いません。

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

「WordPressの有名な5分間インストールプロセスへようこそ!」と表示（@<img>{startaws116}）されたら、サイトのタイトルなどを入力します。サイトのタイトルは好きなものにしてください。ユーザー名やパスワードはWordPressの管理画面にログインするときに使用しますのであなた自身で決めてメモ（@<table>{wpAdminMemo}）しておいてください。「検索エンジンでの表示」はどちらでも構いませんが、Googleなどの検索結果にこのサイトを表示したくなければチェックを入れておきましょう。もしパスワードを忘れてしまった場合、ここに書いたメールアドレス宛てにパスワードリセットのメールが届きますのでメールアドレスは正確に入力してください。すべて入力したら「WordPressをインストール」をクリックします。

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

「WordPress の新しいバージョンがあります。」と表示されていますので「今すぐ更新」をクリック（@<img>{startaws120}）します。

//footnote[security][脆弱性（脆弱性）とは悪用が可能なバグや設定不備のことです。もしWordPressに脆弱性が見つかって修正された新しいバージョンのWordPressが公開されたとしても、あなたが更新をしないとウェブサイトは脆弱性がある危険な状態のままで放置されていることになります。古いバージョンのWordPressを使っているとサイトを改ざんしてウイルスをばらまかれたりデータベースの個人情報を盗まれたりする可能性もありますので、新しいバージョンが出たらきちんと更新しましょう。]

//image[startaws120][「今すぐ更新」をクリック][scale=0.8]{
//}

更新の進捗が表示（@<img>{startaws121}）され、更新完了すると新しいバージョンではどんな修正がされたのか？が表示されます。それではできあがったおしゃれなサイトを見てみましょう。左上の家のマークをクリック（@<img>{startaws122}）してください。

//image[startaws121][更新の進捗が表示される][scale=0.8]{
//}

//image[startaws122][更新完了したら家のマークをクリック][scale=0.8]{
//}

そしてこちらが完成したWordPressのおしゃれなサイトです！（@<img>{startaws123}）ここからは見た目をカスタマイズするもよし、技術的なことを調べたブログ記事を日々綴っていくもよし、自分のサイトを自由に楽しんでください。

//image[startaws123][「自分のサイト」をここからは自由にカスタマイズしよう][scale=0.8]{
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

「New password:」と表示されたら「start-aws-digest-password」と入力してEnterキーを押してください。再度「Re-type new password:」とパスワードを求められますので、再び「start-aws-digest-password」と入力してEnterキーを押します。

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

i（アイ）を押して「編集モード」になったら、次のようにダイジェスト認証の設定（「<Directory "/var/www/start-aws-documentroot/wp-admin">」から「</Directory>」までの6行）を追記してください。

//cmd{
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

続いてブラウザで管理画面（@<href>{http://www.自分のドメイン/wp-admin/}）を開いてみましょう。すると「ユーザー名とパスワードを入力してください」というダイジェスト認証のポップアップが表示（@<img>{startaws125}）されますので、先ほど設定したダイジェスト認証のユーザー名とパスワードを入力して「OK」をクリックしてください。（@<table>{digestAuth}）

//image[startaws125][「ユーザー名とパスワードを入力してください」というダイジェスト認証のポップアップが表示された][scale=0.8]{
//}

//table[digestAuth][ダイジェスト認証の情報]{
------------------------------------
ユーザー名	start-aws-digest-user
パスワード	start-aws-digest-password
//}

正しいユーザー名とパスワードを入れれば管理画面に入るためのログイン画面（もしくは管理画面）が表示（@<img>{startaws127}）されますが、間違ったものを入力すると「Unauthorized」と表示されて管理画面には入れません。これで管理画面は「ダイジェスト認証」と「WordPressの認証」の2段階で守られるようになりました。

//image[startaws127][管理画面が「ダイジェスト認証」と「WordPressの認証」の2段階で守られるようになった][scale=0.8]{
//}

//image[startaws128][正しいユーザー名とパスワードを入れないと「Unauthorized」と表示されて管理画面に入れない][scale=0.8]{
//}

以上でWordPressのインストールは完了です。お疲れさまでした。