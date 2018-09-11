= ウェブサーバの設定をしよう

この章ではウェブサーバの設定を行います。
Apacheでバーチャルホストを作ってブラウザでページを表示してみましょう。

//pagebreak

== ウェルカムページを見てみよう

@<chapref>{serverBuilding}でサーバにApacheをインストールしました。インストールしただけでまだ何の設定もしていませんが、ウェルカムページと呼ばれるデフォルトのページが見られるはずです。しかしブラウザで「@<href>{http://login.自分のドメイン/}」を開いてウェルカムページを見ようとしたところ、「ページ読み込みエラー 接続がタイムアウトしました」「このサイトにアクセスできません。login.自分のドメイン からの応答時間が長すぎます。」といったエラーメッセージが表示（@<img>{startaws57}）されてページを見ることはできませんでした。

//image[startaws57][@<href>{http://login.自分のドメイン/}が見られなかった][scale=0.8]{
//}

これはインスタンスの手前に居るセキュリティグループ@<fn>{securityGroup}が「SSH（ポート番号22番）の通信しか通さない」という設定になっていて、HTTP（ポート番号80番）のリクエストをすべて遮断していることが原因です。@<ttb>{ポート番号とはサーバという家や、その手前にあるセキュリティグループという壁についているドア}のようなものだと思ってください。同じサーバを訪問するときでもSSHは22番のドアを、HTTPは80番のドアを、HTTPSは443番のドアを通ります。

//footnote[securityGroup][セキュリティグループはいわゆる「ファイアウォール」のことです。セキュリティグループってどんなものだったっけ？という方は@<chapref>{serverBuilding}でEC2のインスタンスを作るとき「ステップ6」で設定したことを思い出してください。]

=== セキュリティグループで80番ポートの穴あけをしよう

ウェルカムページが見られるように、セキュリティグループで「HTTP（ポート番号80番）」の穴あけをしましょう。マネジメントコンソールの左上にある「サービス」から、「コンピューティング」の下にある「EC2」（@<img>{startaws58}）をクリックしてください。

//image[startaws58][サービス＞コンピューティング＞EC2][scale=0.8]{
//}

「EC2」をクリックすると、EC2ダッシュボード（@<img>{startaws59}）が表示されます。左メニューの「セキュリティグループ」をクリックしてください。

//image[startaws59][現状はSSH（ポート番号22番）しか通れないので「インバウンド」タブの「編集」をクリック][scale=0.8]{
//}

「ec2-security-group」をクリックして「インバウンド」タブを見ると、現状は通信を許可する対象に「SSH（ポート番号22番）」しか含まれていません。「インバウンド」タブの「編集」をクリックします。

「ルールの追加」をクリックしたらタイプは「HTTP」を選択（@<img>{startaws60}）します。ソースが「カスタム」になり「0.0.0.0/0, ::/0」と自動入力されるので、カンマから後ろを消して「0.0.0.0/0」にしてください。入力できたら「保存」をクリックします。

//image[startaws60][タイプは「HTTP」、ソースは「0.0.0.0/0」にして「保存」をクリック][scale=0.8]{
//}

「インバウンド」タブでHTTPが追加（@<img>{startaws61}）されていたら穴あけ作業は完了です。

//image[startaws61][「インバウンド」タブでHTTPが追加されていたら穴あけ完了][scale=0.8]{
//}

もう一度ブラウザで「@<href>{http://login.自分のドメイン/}」を開いてみましょう。「Amazon Linux AMI Test Page」と書かれたウェルカムページが表示（@<img>{startaws62}）されるはずです。

//image[startaws62][Amazon Linux AMI Test Pageが表示された][scale=0.8]{
//}

== 自分のサイト用にバーチャルホストを作ろう

ここからは自分のサイトの「バーチャルホスト」を作ります。

=== バーチャルホストとは？

「バーチャルホスト」という言葉を聞いたことはありますか？

バーチャルホストというのは@<ttb>{1台のサーバ上で2つ以上のウェブサイトを扱う運用方法のこと}です。

たとえば筆者の趣味が「スイーツブッフェめぐり」と「読書」だったとして、1台のウェブサーバで

 * sweets.startdns.fun
 * book.startdns.fun

という2つのバーチャルホストを作ってやれば、同じサーバ上で別々のサイトを運用できます。マンションの建物（ホストサーバ）の中に101号室や102号室などの各戸（仮想サーバ）があり、その中にはそれぞれ子供部屋や書斎や居間などの部屋（ウェブサイト）があって、その部屋を訪れるお客さんたち（サイトを見る人）がいる、と例えると分かりやすいでしょうか。

これからApacheで自分のサイト用にこのバーチャルホストを作ってみます。

=== バーチャルホストを設定しよう

それでは早速、自分のドメイン（筆者ならstartdns.fun）のサイト用にバーチャルホストを作ってみましょう。@<fn>{subDomain}

//footnote[subDomain][サーバ1台にウェブサイト1つだけであればバーチャルホストにする必要はあまりないのですが、バーチャルホストの作り方を覚えておけば後で「サブドメインで別のサイトを作ってみよう」と思ったときに役立つはずです。]

Windowsの方はRLoginを起動して「start-aws-instance」に接続してください。Macの方はターミナルで次のコマンドを実行してください。

//cmd{
ssh ec2-user@login.自分のドメイン名 -i ~/Desktop/start-aws-keypair.pem
//}

「Amazon Linux AMI」と表示されたら「sudo su -」@<fn>{sudoSu}でrootになりましょう。（@<img>{startaws63}）

//footnote[sudoSu][sudoは「他のユーザとしてコマンドを実行する」ためのコマンドで、 suは「他のユーザになる」ためのコマンドです。「他のユーザ＝root」の場合はユーザ名を書かなくてもいいので省略していますが、省略せずに書くと「sudo -u root su - root」（rootとして「rootになる」というコマンドを実行する）ということです。ちなみに勘違いされることが多いですがsuは「Super User」ではなく「Substitute User（ユーザーを代用する）」の略です。]

//cmd{
$ sudo su -
//}

//image[startaws63][Amazon Linux AMIと表示されたらrootになろう][scale=0.8]{
//}

Apacheの大本となる設定ファイルは「/etc/httpd/conf/httpd.conf」です。350行以上あるのでtailコマンドを使って最後の5行だけ確認してみましょう。

//cmd{
# tail -5 /etc/httpd/conf/httpd.conf
//}

//image[startaws143][tailコマンドでhttpd.confの最後の5行を見てみよう][scale=0.8]{
//}

すると最後の行に

//cmd{
IncludeOptional conf.d/*.conf
//}

とあるため大本の設定ファイルの中で、さらに「conf.d」というディレクトリ内の「*.conf」というファイルをインクルード（取り込み）@<fn>{includeOptional}していることが分かります。でもいきなり「conf.d/*.conf」と書かれても「3丁目」とだけ書かれた住所のようなもので、どこの「conf.d/*.conf」を指しているのかよく分かりませんよね。「conf.d」より上のディレクトリはどこで指定しているのか、grepという検索のコマンドで探してみましょう。

//footnote[includeOptional][IncludeディレクティブやIncludeOptionalディレクティブについては@<href>{https://httpd.apache.org/docs/2.4/ja/mod/core.html#include}を参照。]

//cmd{
# grep "^ServerRoot" /etc/httpd/conf/httpd.conf
ServerRoot "/etc/httpd"
//}

ServerRoot@<fn>{serverRoot}ではベースとなるディレクトリを指定しています。これで「conf.d/*.conf」が実際は「/etc/httpd/conf.d/*.conf」であることが分かりました。

//footnote[serverRoot][ServerRootディレクティブについては@<href>{https://httpd.apache.org/docs/2.4/ja/mod/core.html#serverroot}を参照。]

では自分のドメインのサイト用にバーチャルホストを「/etc/httpd/conf.d」の下で作成してみましょう。viコマンドで新しい設定ファイルを作ります。

//cmd{
# vi /etc/httpd/conf.d/start-aws-virtualhost.conf
//}

こんな画面（@<img>{startaws64}）で「"/etc/httpd/conf.d/start-aws-virtualhost.conf" [New File]」と表示されましたか？

//image[startaws64][viでバーチャルホストの設定ファイルを作ろう][scale=0.8]{
//}

この状態でi（アイ）を押して（@<img>{startaws65}）左下に「-- INSERT --」と表示されたら「編集モード」になっています。

//image[startaws65][i（アイ）を押すと「-- INSERT --」と表示される「編集モード」になった][scale=0.8]{
//}

「編集モード」になったら次のようにバーチャルホストの設定を書いていってください。「自分のドメイン」のところはそのまま日本語で書かず、自分のドメイン名に置き換えてください。

//cmd{
<VirtualHost *:80>
    DocumentRoot "/var/www/start-aws-documentroot"
    ServerName www.自分のドメイン

    ErrorLog "logs/start-aws-error.log"
    CustomLog "logs/start-aws-access.log" combined

    <Directory "/var/www/start-aws-documentroot">
        AllowOverride All
    </Directory>
</VirtualHost>
//}

書き終わったらESCキーを押す（@<img>{startaws66}）と左下の「-- INSERT --」が消えて再び「閲覧モード」になります。

//image[startaws66][ESCを押すと左下の「-- INSERT --」が消えて再び「閲覧モード」になる][scale=0.8]{
//}

「閲覧モード」に戻ったら「:wq」と入力してEnterキーを押せば保存されます。（@<img>{startaws67}）

//image[startaws67][「閲覧モード」に戻ったら「:wq」と入力してEnterキーを押せば保存される][scale=0.8]{
//}

では確認のため、次のコマンドを叩いてみてください。

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
</VirtualHost>
//}

「ServerName」のところが日本語の「www.自分のドメイン」ではなく、ちゃんと自分のドメインに置き換わっているか確認してください。たとえば筆者なら「startdns.fun」というドメインなので次のようになっています。

//cmd{
ServerName www.startdns.fun
//}

もしcatコマンドを叩いたときに「そのようなファイルやディレクトリはありません」と表示されたら設定ファイルが作成できていません。作り直しましょう。

=== 設定ファイルの構文チェック

バーチャルホストの設定ファイルが書けたのでapachectlで構文チェックをしてみましょう。apachectlはApacheを操作するためのコントローラのようなもので、引数にconfigtestとつけてやると設定ファイルの構文チェックができます。

//cmd{
# apachectl configtest
AH00112: Warning: DocumentRoot [/var/www/start-aws-documentroot] does not exist
Syntax OK
//}

早速警告のメッセージが表示されています。落ち着いて読んでみましょう。「DocumentRoot [/var/www/start-aws-documentroot] does not exist」と書いてあります。これは「ドキュメントルートに[/var/www/start-aws-documentroot]というディレクトリを指定しているけどそんなディレクトリ存在しないよ」と言っているのです。

=== ドキュメントルートを作成

ドキュメントルート@<fn>{docRoot}とは「サイトにアクセスしたらここに置いたファイルが表示されるよ」というディレクトリのことです。つまりバーチャルホストの設定で

//footnote[docRoot][@<href>{https://httpd.apache.org/docs/2.4/ja/mod/core.html#documentroot}]

//cmd{
DocumentRoot "/var/www/start-aws-documentroot"
ServerName www.startdns.fun
//}

と書いてあったら、

//cmd{
/var/www/start-aws-documentroot/
//}

に置いた「index.html」が@<href>{http://www.startdns.fun/index.html} で見られるということです。

先ほどバーチャルホストの設定で次のように書いたのですが、このディレクトリがまだ存在していないため警告が出てしまっているようです。ですのでこのディレクトリを作成しましょう。

//cmd{
DocumentRoot "/var/www/start-aws-documentroot"
//}

ディレクトリを作るにはmkdir@<fn>{mkdir}というコマンドを使います。mkdirコマンドでディレクトリを作ったら、ちゃんと作成できたかlsコマンドで確認してみましょう。

//footnote[mkdir][mkdirはMaKe DIRectoryの略。]

//cmd{
# mkdir /var/www/start-aws-documentroot

# ls -l /var/www/
合計 24
drwxr-xr-x 2 root root 4096  8月 18 07:22 cgi-bin
drwxr-xr-x 3 root root 4096  9月  1 17:43 error
drwxr-xr-x 2 root root 4096  8月 18 07:22 html
drwxr-xr-x 3 root root 4096  9月  1 17:43 icons
drwxr-xr-x 2 root root 4096  9月  1 17:43 noindex
drwxr-xr-x 2 root root 4096  9月  4 12:53 start-aws-documentroot
//}

これでドキュメントルートができました。再びapachectlで構文チェックをしてみましょう。今度は「Syntax OK」とだけ表示されるはずです。

//cmd{
# apachectl configtest
Syntax OK
//}

=== index.htmlを置いてみよう

ドキュメントルートを用意したのですが、何かしらコンテンツを置いておかないとアクセスしたときに「404 Not Found」になってしまうので、viコマンドでドキュメントルートの下にindex.htmlのファイルを用意しておきましょう。

//cmd{
# vi /var/www/start-aws-documentroot/index.html
//}

i（アイ）を押して「編集モード」に変わったら「AWSをはじめよう」と書いてみましょう。（@<img>{startaws68}）

//image[startaws68][i（アイ）を押して「-- INSERT --」と表示されたら「AWSをはじめよう」と書いてみよう][scale=0.8]{
//}

書き終わったらESCキーを押して「閲覧モード」に戻り、「:wq」と入力してEnterキーを押して保存しましょう。（@<img>{startaws69}）

//image[startaws69][ESCを押して「閲覧モード」に戻ったら「:wq」で保存][scale=0.8]{
//}

それではバーチャルホストの設定を有効にするため、apachectlでApacheを再起動しましょう。

//cmd{
# apachectl restart
//}

何のメッセージも表示されなければ問題なくApacheが再起動できています。

=== curlでページを確認しよう

これでバーチャルホストの設定は完了です。ウェブサーバに「自分のウェブサイトのページ見せて」と頼んだら、ちゃんとウェブページを返してくれるのか確認してみましょう。次のようなコマンドを叩いてみてください。「www.自分のドメイン」の部分は自分のドメインに置き換えます。たとえば筆者なら「startdns.fun」というドメインなので「www.startdns.fun」にします。

//cmd{
# curl -H "Host:www.自分のドメイン" http://localhost/index.html
AWSをはじめよう
//}

これはcurl（カール）という「ターミナルにおけるブラウザ」のようなコマンドを使って、localhost（自分自身）の「www.自分のドメイン名」というホストに対して「ページ見せて」というリクエストを投げています。ちゃんと自分のバーチャルホストが応答して、ドキュメントルートにあるindex.htmlの「AWSをはじめよう」が表示されましたね。

== Route53で自分のサイトのドメインを設定しよう

続いてブラウザでも「@<href>{http://www.自分のドメイン}」を開いてサイトを確認してみましょう。（@<img>{startaws70}）するとなんと「アクセスしようとしているサイトを見つけられません。」と表示されてしまいました。

//image[startaws70][ブラウザで「www.自分のドメイン」を開いたらエラーになってしまった][scale=0.8]{
//}

これはまだ「www.自分のドメイン」というドメイン名とサーバのIPアドレスをつなぐAレコードが存在していないからです。Route53でAレコードを作りましょう。

=== 自分のサイトのドメイン名を作ろう

マネジメントコンソールの左上にある「サービス」から、「ネットワーキング＆コンテンツ配信」の下にある「Route53」（@<img>{startaws71}）をクリックしてください。

//image[startaws71][サービス＞ネットワーキング＆コンテンツ配信＞Route53][scale=0.8]{
//}

Route53ダッシュボードを開いたらDNS managementの「Hosted zones」をクリック（@<img>{startaws72}）します。

//image[startaws72][「Hosted zones」をクリック][scale=0.8]{
//}

Domain Nameの自分のドメイン名（筆者の場合はstartdns.fun）をクリック（@<img>{startaws73}）します。

//image[startaws73][自分のドメイン名をクリック][scale=0.8]{
//}

「Create Record Set」をクリック（@<img>{startaws74}）してください。すると右側にリソースレコードの情報を入力するフォームが出てきます。

//image[startaws74][「Create Record Set」をクリック][scale=0.8]{
//}

Nameには「www」、ValueにはElastic IPを入力（@<img>{startaws75}）します。Elastic IPは左側の「login.自分のドメイン名」のところにも書いてあるので、それをコピーしてきても構いません。入力できたら「Create」をクリックします。

//image[startaws75][Nameには「www」、Valueにはloginと同じElastic IPを入力][scale=0.8]{
//}

これで「www.自分のドメイン名」（@<img>{startaws76}）というAレコードが作成できました。

//image[startaws76][「www.自分のドメイン名」というAレコードができた][scale=0.8]{
//}

=== 【ドリル】/（スラッシュ）で終わるURLを開いたときにindex.html以外を返したい

==== 問題

@<href>{http://www.startdns.fun/}を開くとファイル名は指定していないのにindex.htmlが表示されます。このようにファイル名を省略して「/（スラッシュ）」で終わるURLを開いたとき、index.htmlではなくneko.htmlを表示させたかったらApacheの設定ファイル（httpd.conf）でどの設定を書き換えればよいでしょうか？

 * A. DirectorySlashディレクティブ
 * B. DirectoryIndexディレクティブ
 * C. Directoryディレクティブ

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。grepコマンドを使ってApacheの設定ファイル（httpd.conf）で「index.html」を検索してみると、次のような設定が見つかります。

//cmd{
# grep index.html /etc/httpd/conf/httpd.conf 
    DirectoryIndex index.html
//}

DirectoryIndexディレクティブではファイル名を省略して「/（スラッシュ）」で終わるURLを開いたときに返すファイルの名前を指定できます。次のように複数指定した場合は「index.html」「index.php」「index.txt」の順に探して、最初に見つかったものを返します。

//cmd{
DirectoryIndex index.html index.php index.txt
//}

=== ブラウザでページを見てみよう

Aレコードの追加が終わったら再びブラウザで「@<href>{http://www.自分のドメイン}」を開いてみましょう。（@<img>{startaws77}）今度こそindex.htmlの「AWSをはじめよう」が表示されました。おめでとうございます！

//image[startaws77][index.htmlの「AWSをはじめよう」が表示された][scale=0.8]{
//}

=== アクセスログとエラーログの大切さ

ブラウザ上ではサイトが表示されましたが、サーバ側でもアクセスログを確認してみましょう。

//cmd{
# tailf /etc/httpd/logs/start-aws-access.log
//}

tailfコマンド@<fn>{tailf}はファイルの追記を監視できるコマンドなので、今来ているアクセスのログをタイムリーに確認できます。何回かEnterキーを叩いて改行したら、この状態でブラウザの更新ボタンをクリックしてみましょう。自分がいまブラウザでアクセスしたログが次々と表示されると思います。（@<img>{startaws78}）tailfコマンドはCtrl+cで抜けるまでずっとログの追記が表示され続けます。

//footnote[tailf][tailコマンドに-fオプションをつけてもまったく同じ動作をします。]

//image[startaws78][tailfでログを確認しながらブラウザでサイトの表示を更新してみよう][scale=0.8]{
//}

念のためエラーログも確認してみましょう。アクセスログ（1.6K）に対してエラーログはファイルサイズが0です。エラーログは1行も出ていないようですので問題ありません。

//cmd{
# ls -lh /etc/httpd/logs/start-aws-*
-rw-r--r-- 1 root root 1.6K  9月  4 13:51 /etc/httpd/logs/start-aws-access.log
-rw-r--r-- 1 root root    0  9月  4 13:07 /etc/httpd/logs/start-aws-error.log
//}

たとえばサイトが上手く表示されないとき、アクセスログやエラーログを確認すれば「サーバまでたどり着いていない」のか「サーバにはたどり着いているけれど、ドキュメントルートに置いたPHPファイルのエラーでちゃんとページが出ない」のか、といった問題の切り分けができます。上手くいかないときはログを見るようにしましょう。