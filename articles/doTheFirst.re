= AWSを使い始めたら最初にやること

この章ではAWSの管理画面にサインインして、AWSを使い始めたら最初にやるべき設定を実践していきます。
初期設定とかいいから早くサーバ立てたい！という気持ちだと思いますが、あなたのお財布を守るため最初にしっかりセキュリティを強化しておきましょう。

//pagebreak

== AWS無料利用枠を使おう

AWSを初めて使用する場合、AWSアカウントを作成してから1年間は利用料が無料となります。但し、無料利用枠の範囲は決まっており、何をどれだけ使っても無料という訳ではありません。何もかも全部無料だと思ってサーバをバカスカ立てると、あとでクレジットカードにしっかり請求が来ますので注意してください。

どのサービスをどれくらい無料で使えるのか？は「AWS無料利用枠の詳細（@<href>{https://aws.amazon.com/jp/free/}）」（@<img>{awsFree}）に「Amazon EC2はt2.microインスタンスが月に750時間無料」、「Amazon EBSは30GB無料」のように細かく書かれていますので、そちらを参照してください。@<fn>{whatIsEC2}

//image[awsFree][AWS無料利用枠の詳細][scale=0.8]{
//}

//footnote[whatIsEC2][EC2ってなに？EBSってなに？は後述します。]

なお本著で使用するAWSのサービスは、基本的にこの無料利用枠の範囲内に収まるようにしています。但し、Route53というネームサーバのサービスなど、一部は無料利用枠の対象外となるため毎月50セント～数ドル程度かかりますのでその点はご留意ください。

うっかり多額の請求が来ても筆者が代わりに支払うことはできません@<fn>{canNot}ので、そうならないよう後ほど「利用金額が○円を超えたらメールで知らせる」という請求アラートの設定をしっかりしておきましょう。

//footnote[canNot][できませんできません、人間にはこんなこと絶対にできません。]

== AWSのアカウント作成

AWSを使うには、先ずAWSアカウントを作成する必要があります。

AWSアカウントの作成は「DNSをはじめよう」（@<img>{startDNS}）@<fn>{booth}の「第3章 AWSのネームサーバ（Route53）を使ってみよう」で済ませていますので、本著でもそのAWSアカウントを引き続き使用していきます。

//footnote[booth][@<href>{https://mochikoastech.booth.pm/}]

まだAWSアカウントを持っていない！作っていない！という人は、先に「DNSをはじめよう」で、

  1. ドメインを買う
  2. AWSのアカウントを作る
  3. ネームサーバとしてAWSのRoute53を使う

という3つのステップを踏んでから、この先へ進むようにしてください。

//image[startDNS][「DNSをはじめよう」（1,000円）はBOOTHで好評発売中][scale=0.5]{
//}

===[column] 【コラム】「DNSをはじめよう」はどこで買える？

「AWSをはじめよう」の前作である「DNSをはじめよう」（通称DNS本）は書籍版、PDFダウンロード版ともにBOOTH@<fn>{howToBuy}で購入できます。

//footnote[howToBuy][@<href>{https://mochikoastech.booth.pm/}]

BOOTHはピクシブ株式会社@<fn>{pixiv}が運営している同人誌の通販及びダウンロード販売サイトで、書籍版を購入すると1～2営業日以内にBOOTH倉庫からネコポスで本が送られてきます。PDF版なら購入後すぐにダウンロードして読むことができます。技術書典で頒布されている同人誌の多くはBOOTHでも購入できますので、気になる方は「技術書典」のタグで検索@<fn>{techBookFest}してみることをお勧めします。

//footnote[pixiv][イラストを投稿できるSNS、pixivでお馴染み。@<href>{https://www.pixiv.net/}]
//footnote[techBookFest][@<href>{https://booth.pm/ja/search/技術書典}]

本といえばAmazonなので「Amazonで売ってくれないかな？」と思われる方も多いと思うのですが、そもそもAmazonでは同人誌が販売できないため、Amazonで売るためには先ずはISBNコード（商業誌の裏表紙にあるバーコードとその下の番号）を頑張って取らねばなりません。そこに労力を割くよりは、いい本を書く方向で頑張ろうと思いますのでどうぞご理解ください。

ちなみに「DNSをはじめよう」は、ただのDNS好きである筆者がDNSへのあふれんばかりの愛を早口で詰め込んだ本ですが、技術書典4当日に750冊、その後もダウンロード販売で売れ続けて累計1300冊以上（2018年8月現在）という驚きの頒布数となりました。手にとって、買って、読んでくださった皆さん、ありがとうございます。

===[/column]

== マネジメントコンソールにサインイン

それでは早速、AWSのサインイン画面（@<href>{https://console.aws.amazon.com/}）を開いて（@<img>{consoleSignin}）、マネジメントコンソールにサインインしましょう。サインインという言葉には馴染みがないかも知れませんが、「ログイン」と同じ意味です。

//image[consoleSignin][マネジメントコンソールのサインイン画面][scale=0.8]{
//}

先ずはAWSアカウントのEメールアドレスを入力して「次へ」、続いてルートユーザーサインインの画面（@<img>{enterPassword}）でパスワードを入力して「サインイン」ボタンを押します。

//image[enterPassword][Eメールアドレスを入力後、パスワードを入力してサインイン][scale=0.8]{
//}

無事にサインインできたら、マネジメントコンソール（@<img>{managementConsole}）が表示されます。皆さんもサインインできましたか？

//image[managementConsole][マネジメントコンソール（AWSの管理画面）][scale=0.8]{
//}

このマネジメントコンソールが、AWSの管理画面となります。これからサーバを立てたりする作業は、すべてこの画面で行っていきます。

=== 【ドリル】AWSの管理画面はなんて名前？

==== 問題

AWSの管理画面はなんと呼ばれているでしょう？

 * A. コントロールパネル
 * B. マネジメントコンソール
 * C. クラウドコンソール


//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBのマネジメントコンソールです。マネジメントコンソールにはサインイン画面（@<href>{https://console.aws.amazon.com/}）からサインインします。AWSを使うときは、このマネジメントコンソールで色々な操作をしますので、名前を覚えておいてください。

== IAMでユーザの権限管理

=== ルートユーザーの普段使いはやめよう

さて、皆さんがいまサインインに使ったのは「ルートユーザー」と呼ばれるユーザです。実はルートユーザーは全権を持っていてなんでもできるユーザなので、普段からこのユーザを使って色々な操作をするのはお勧めしません。

「ルートユーザってなんでもできるユーザなんでしょ？大は小を兼ねるっていうし、便利なんだからそれ使えばいいじゃない」と思われるかも知れませんが、最寄のスーパーまで晩御飯の買い物に行くだけなのに、1,000万円と利用上限額なしのクレジットカードをアタッシュケースに詰めて持っていく人は居ないですよね？子供の財布なら1,000円くらい、自分の財布なら20,000円くらい、のように使う人によって使える金額を制御しておくことで、財布を落としたり盗まれたりしたときのダメージを少なくしておくのは、誰しも無意識にやっているセキュリティ対策だと思います。

AWSのユーザにはクレジットカードを紐付けているのですから、お財布もルートユーザーも等しく扱いには気をつけなければいけません。たとえば悪い人があなたのルートユーザのEメールアドレスとパスワードを盗んで、こっそりマネジメントコンソールにサインインしたとします。ルートユーザーならなんでもできるので、景気良くいちばん高いサーバ@<fn>{d28xlarge}を100台立てた@<fn>{reasonWhy}としましょう。その場合、1日で180万円かかるので、1ヶ月後には5,400万円の請求@<fn>{mustPay}があなたのところへやってきます。（@<img>{awsUnauthorizedUse}）

//image[awsUnauthorizedUse][「AWS 不正利用」で検索すると不正利用による請求で青ざめた体験記がたくさん][scale=0.8]{
//}

//footnote[d28xlarge][EC2のd2.8xlargeというサーバは、東京リージョンだと1時間あたり6.752ドル。日本円にすると1日でおおよそ18,000円です。もちろん大量に立てられないように台数制限はありますが、ルートユーザーならその制限を緩和するリクエストを出すことだって可能です。]
//footnote[reasonWhy][そんなにいっぱいサーバを立ててどうするの？と思いますよね。なんと悪い人たちは他人のアカウントで高スペックのサーバを大量に立てて、ビットコインを生み出すためのマイニング（採掘）をするのです。]
//footnote[mustPay][不正利用による請求であっても本来は契約者に支払い義務がありますが、ネット上の体験記を見ると支払いを免除あるいは返金してもらえることが多いようです。もし心当たりのない多額の請求が来たら落ち着いてサポートに問い合わせてみましょう。]

このようにルートユーザーだとなんでもできてしまうため、権限が必要ないときにまでルートユーザーを使うのは大変危険です。繰り返しになりますが、1,000万円とクレジットカードが詰まったアタッシュケースを持って、うっきうきでスーパーマーケットに行くのは危ないのでやめましょう。

=== IAMユーザを作ろう

という訳でルートユーザではなく、必要な作業ができる権限だけを持った自分用の「IAMユーザー」というユーザを作って普段はそちらを使いましょう。

==== IAMってなに？

IAMはIdentity and Access Managementの略で、AWSの利用を安全に管理するためのサービスです。

ある程度の規模の会社であれば、1つの鍵をみんなで使いまわしたりせずひとりひとりにIDカードが付与されていますよね。オフィスを安全に利用するため、IDカードを使うことで社内の人間しかオフィスフロアへ入れないようになっていたり、特定のプロジェクトルームにはそこのプロジェクトメンバーしか入れないようになっていたりします。

IAMも同じでAWSを利用する人を限定したり、サービスによって使える人を絞ったりすることができます。

==== IAMユーザーは1人に1つ

本著では1人だけで作業をする想定なので、IAMユーザーも1人しか作りません。ですがもし業務などで複数名でマネジメントコンソールにサインインする場合は、IAMユーザーは必ず1人につき1つずつ作成してください。まったく同じ作業をするから開発チーム内のAさんとBさんは同じIAMユーザを共有すればいいのでは？と思われる場合でも、必ずAさんBさんそれぞれに別々のIAMユーザーを用意することをお勧めします。

なぜならばAWSでは「いつ・どのIAMユーザーが・なにをしたのか」をすべて記録していて、後から調べることができるのですが、仮にAさんとBさんが1つのIAMユーザーを共用していた場合、何か重大なトラブルが起きたとき@<fn>{troubleHappened}に「結局、誰がやらかしたのか？」を人単位で追いかけることができなくなってしまうからです。

//footnote[troubleHappened][想像もしたくないですが、たとえば誰かがすべてのサーバをバックアップ含めてすべてきれいに削除してしまった、とか。IAMユーザーを共用していると、使っていた人全員に疑いがかかってしまいます。]

==== IAMダッシュボード

それではマネジメントコンソールの左上にある「サービス」から、「セキュリティ、アイデンティティ、コンプライアンス」の下にある「IAM」（@<img>{iam}）をクリックしてください。

//image[iam][サービス＞セキュリティ、アイデンティティ、コンプライアンス＞IAM][scale=0.8]{
//}

「IAM」をクリックすると、IAMのダッシュボード（@<img>{iamDashboard}）が表示されます。

//image[iamDashboard][IAMダッシュボード][scale=0.8]{
//}

==== IAMのグループを作成

では先ずIAMダッシュボードの左メニューから「グループ」を選んでください。

IAMではグループを作成して、そのグループに対して権限を設定し、個々のIAMユーザはグループに所属させることでアクセス権限を管理できます。たとえば前述のような「開発チームのAさんとBさんにはまったく同じ権限を付与したい」という場合に、先にdevelopersというグループを作って、developersグループに権限を付与しておけば、AさんBさんのIAMユーザはdevelopersグループに所属させるだけで必要な権限を渡すことができます。

今はまだIAMにグループが1つもないため、先ずはグループを作りましょう。左上の「新しいグループの作成」をクリック（@<img>{addGroup}）します。

//image[addGroup][左メニューの「グループ」＞「新しいグループの作成」をクリック][scale=0.8]{
//}

ここから3つの手順で新しいグループを作成していきます。

先ずは手順1の「グループ名」です。本著ではIAMのグループは「start-aws-group」にします。グループ名の欄に「start-aws-group」と入力して、右下の「次のステップ」をクリック（@<img>{addGroupStep1}）してください。

//image[addGroupStep1][グループ名に「start-aws-group」と入力して「次のステップ」をクリック][scale=0.8]{
//}

続いて手順2の「ポリシーのアタッチ」でグループに対してポリシーを紐付けます。なんだかものすごくたくさん並んでいますが、それぞれ「どのサービスでどんな操作を許可する」というポリシー（方針）ですので、そこから必要なポリシーを選択してグループにアタッチ（紐付け）していきます。

たくさんあるのでここでは2つだけ紹介します。先ほどのルートユーザーと同様に何でもできる1番権限の強いポリシーが「AdministratorAccess」です。そして「AdministratorAccess」からIAMに関する権限だけを引いたのが「PowerUserAccess」という、2番目に権限の強いポリシーです。

本来は必要最小限の権限だけを付与するべきですが、今回は細かな設定はせずにこの1番強力な「AdministratorAccess」というポリシーを「start-aws-group」にアタッチします。@<fn>{administratorAccess}フィルターに「AdministratorAccess」と入力して、下に表示された「AdministratorAccess」にチェックを入れたら、右下の「次のステップ」をクリック（@<img>{addGroupStep2}）してください。

//footnote[administratorAccess][え、大金の詰まったアタッシュケース持って買い物に行っちゃうの？！と思ったあなたは正しいです。ですがポリシーを細かにアタッチしていく作業をすべて解説するのは紙面の都合上難しいため、ここでは「普段はルートユーザーではなくIAMユーザーを使うべき」「本来はIAMユーザーには必要最小限の権限だけを付与すべき」ということだけ覚えておいて先へ進みましょう。]

//image[addGroupStep2][「AdministratorAccess」にチェックを入れて「次のステップ」をクリック][scale=0.8]{
//}

最後に手順3の「確認」です。グループ名とポリシーを確認したら、右下の「グループの作成」をクリック（@<img>{addGroupStep3}）します。

 * グループ名：start-aws-group
 * ポリシー：arn:aws:iam::aws:policy/AdministratorAccess

//image[addGroupStep3][グループ名とポリシーを確認して右下の「グループの作成」をクリック][scale=0.8]{
//}

IAMのグループ一覧に、今作ったばかりの「start-aws-group」というグループが表示（@<img>{addGroupFinish}）されたらグループの作成は完了です。

//image[addGroupFinish][「start-aws-group」というグループが作成できた][scale=0.8]{
//}

==== IAMのユーザを作成

IAMのグループが作成できたので、続いてIAMユーザーを作成しましょう。左メニューから「ユーザー」を選ぶと、ユーザーの一覧画面（@<img>{selectUser}）が表示されます。まだIAMユーザーが1つも存在しないため、「IAMユーザーが存在しません。」と表示されています。それでは上部の「ユーザーを追加」をクリックしてください。

//image[selectUser][左メニューの「ユーザー」＞「ユーザーを追加」をクリック][scale=0.8]{
//}

ここから3つのステップでIAMユーザーを追加していきます。

先ずはステップ1（@<img>{iamStep1}）です。IAMのユーザー名を入力してください。本著ではIAMのユーザ名は「start-aws-user」にします。IAMのユーザー名はこの後もサインイン時に使用しますので、もし別のユーザー名にした場合は、しっかりメモしておいてください。

続いてこのIAMユーザーでAWSにアクセスする方法を選択します。AWSでたとえば「サーバを立てる」「サーバを削除する」などの操作をするには、

  1. プログラムからAWSのAPIを叩いて操作する方法
  2. ブラウザでマネジメントコンソールを開いて画面上で操作する方法

の2つがあります。本著ではマネジメントコンソールからしか操作しないため、「アクセスの種類」は「AWSマネジメントコンソールへのアクセス」にのみチェックを入れてください。

ユーザー名を入力して、アクセスの種類を選択したら「次のステップ: アクセス権限」をクリックします。

//image[iamStep1][ユーザー名をstart-aws-userにして、AWSマネジメントコンソールへのアクセスにチェック][scale=0.8]{
//}

続いてステップ2（@<img>{iamStep2}）です。先に作っておいた「start-dns-group」というグループに、ユーザーを追加します。「start-dns-group」にチェックを入れたら、「次のステップ: 確認」をクリックしてください。

//image[iamStep2][「start-aws-group」にチェックを入れて、「次のステップ: 確認」をクリック][scale=0.8]{
//}

最後にステップ3です。次の4つを確認して、問題なければ「ユーザーの作成」をクリック（@<img>{iamStep3}）してください。

  1. ユーザー名が「start-aws-user」であること
  2. AWSアクセスの種類が「AWS マネジメントコンソールへのアクセス - パスワードを使用」であること
  3. グループが「start-aws-group」であること
  4. 管理ポリシーが「IAMUserChangePassword」であること

//image[iamStep3][確認して問題なければ「ユーザーの作成」をクリック][scale=0.8]{
//}

「成功」と表示されたらIAMユーザーの作成は完了です。（@<img>{iamStepFinish}）

//image[iamStepFinish][「成功」と表示されたらIAMユーザーの作成完了][scale=0.8]{
//}

この画面で表示されるURLの数字（@<img>{accountNumber}）とパスワード（@<img>{password}）は、この後サインインするときに使用しますので必ずメモ（@<table>{iamUserData}）しておいてください。

//image[accountNumber][URLの数字をメモしておこう][scale=0.8]{
//}

//image[password][パスワードの「表示」をクリックして、パスワードもメモしておこう][scale=0.8]{
//}

//table[iamUserData][IAMユーザの情報]{
	例	自分のIAMユーザー情報
------------------------------------
AWSアカウント（URLの数字）	432265422850	
ユーザー名	start-aws-user	
パスワード	7*LF8%PkR|UD	
//}

メモができたら、続けて右下の「Eメールの送信」をクリック（@<img>{sendEmail}）します。サインインURLやIAMのユーザー名は忘れやすいので、メールでも自分自身宛てに送っておくことをお勧めします。

//image[sendEmail][サインインURLやIAMユーザー名をメールで自分自身宛てに送っておこう][scale=0.8]{
//}

しっかりメモをしてメールも送ったら、「成功」と表示された画面で「https://************.signin.aws.amazon.com/console」と書いてあるURLをクリックします。するとブラウザの別タブでIAMユーザーのサインイン画面が開いて、自動的に元のタブのルートユーザーはサインアウト（@<img>{signOut}）させられます。サインアウトしてしまったタブは閉じてしまって構いません。

//image[signOut][ルートユーザーでサインインしていた画面は自動的にサインアウトされる][scale=0.8]{
//}

別タブで開いたIAMユーザーのサインイン画面（@<img>{signIn}）で、先ほどメモしたユーザー名とパスワードを入力して「サインイン」をクリックします。

//image[signIn][ユーザー名とパスワードを入力して「サインイン」をクリック][scale=0.8]{
//}

サインインすると、新しいパスワードの設定画面（@<img>{changePassword}）が表示されます。「古いパスワード」に先ほどメモしたパスワードを、「新しいパスワード」には今新たに自分で考えたパスワードを入力してください。すべて入力したら「パスワード変更の確認」をクリックします。

//image[changePassword][新しいパスワードを入力して「パスワード変更の確認」をクリック][scale=0.8]{
//}

ここで再びAWSアカウント、ユーザー名、新しいパスワードをメモ（@<table>{iamUserDataAgain}）しておきましょう。

//table[iamUserDataAgain][IAMユーザの情報]{
  例  自分のIAMユーザー情報
------------------------------------
AWSアカウント（URLの数字）	432265422850	
ユーザー名	start-aws-user	
新しいパスワード	自作のパスワード	
//}

IAMユーザーで無事にサインインできたら、マネジメントコンソール（@<img>{iamUserSignin}）が表示されます。皆さんもサインインできましたか？

//image[iamUserSignin][IAMユーザーでサインインできた！][scale=0.8]{
//}

右上のIAMユーザー名をクリック（@<img>{checkUsername}）すると、IAMユーザー名とAWSアカウントが表示されます。ここでルートユーザーではなくIAMユーザーでサインインしていることが確認できます。

//image[checkUsername][IAMユーザーでサインインしていることを確認][scale=0.8]{
//}

これでルートユーザーではなく、IAMユーザーでマネジメントコンソールにサインインできるようになりました。

=== MFA（多要素認証）で不正利用からIAMユーザーを守る

無事にIAMユーザーでサインインできたら、再び左上にある「サービス」から「IAM」をクリックしてください。もしくは「最近アクセスしたサービス」から「IAM」をクリック（@<img>{accessService}）でも構いません。

//image[accessService][「最近アクセスしたサービス」から「IAM」をクリック][scale=0.8]{
//}

IAMのダッシュボードが表示されたら、左メニューの「ユーザー」をクリック（@<img>{clickUser}）します。

//image[clickUser][左メニューの「ユーザー」をクリック][scale=0.8]{
//}

現状は、

  1. AWSアカウント（12桁の数字）
  2. ユーザー名
  3. パスワード

の3つがあれば、IAMユーザーでサインインできてしまいます。ですがMFA（多要素認証）@<fn>{mfa}を有効にすると「AWSアカウントとユーザー名とパスワード」に加えて、ユーザーが持っているスマホの認証アプリなど別の要素を使って本人か確認することになるため、より安全にアカウントを管理できます。

//footnote[mfa][AWS Multi-Factor Authenticationの略。]

今はまだMFAが有効になっていない（@<img>{mfaOff}）ため、有効にしてみましょう。ユーザー名の「start-aws-user」をクリックします。

//image[mfaOff][ユーザー名の「start-aws-user 」をクリック][scale=0.8]{
//}

「認証情報」タブの「MFA デバイスの割り当て いいえ」の横にあるエンピツマークをクリック（@<img>{selectMfaDevice}）します。

//image[selectMfaDevice][「MFA デバイスの割り当て いいえ」の横にあるエンピツマークをクリック][scale=0.8]{
//}

多要素認証をするときは、キーホルダーやカードの形をした専用のMFAデバイス（@<img>{realDevice}）@<fn>{amazonURL}を買って使うか、もしくは「Google認証システム（Google Authenticator）」というスマホの認証アプリを擬似的なMFAデバイスとして使用します。

//image[realDevice][キーホルダータイプのMFAデバイス][scale=0.8]{
//}

//footnote[amazonURL][@<href>{https://www.amazon.co.jp/dp/B019THYZGE}]

言葉で説明しても分かりにくいと思うので実際にやってみましょう。有効にするMFAデバイスタイプは「仮想MFAデバイス」を選択（@<img>{virtualDevice}）して 「次のステップ」をクリックしてください。

//image[virtualDevice][「仮想MFAデバイス」を選択して 「次のステップ」をクリック][scale=0.8]{
//}

お手元のスマホに「Google認証システム（Google Authenticator）」をインストール@<fn>{googleAuthenticator}したら「次のステップ」をクリック（@<img>{installVirtualDevice}）します。

//footnote[googleAuthenticator][Androidなら@<href>{https://play.google.com/store/apps/details?id=com.google.android.apps.authenticator2}、iPhoneなら@<href>{https://itunes.apple.com/jp/app/google-authenticator/id388497605}からインストールできます。Androidの場合は元々入っているかも知れません。]

//image[installVirtualDevice][スマホに認証アプリをインストールしたら 「次のステップ」をクリック][scale=0.8]{
//}

続いてスマホで「Google認証システム」のアプリを起動したら右下の赤い＋ボタンをタッチ（@<img>{mfaAppli01}）して、「バーコードをスキャン」を選択（@<img>{mfaAppli02}）します。

//image[mfaAppli01][「Google認証システム」のアプリを起動したら右下の赤い＋ボタンをタッチ][scale=0.3]{
//}

//image[mfaAppli02][「バーコードをスキャン」を選択][scale=0.3]{
//}

「Google認証システム」のアプリで「赤線内にバーコードを配置してください」（@<img>{mfaAppli03}）と表示されたら、マネジメントコンソールに表示されたバーコード（@<img>{barcode}）がスマホの赤枠内に収まるようにします。

//image[mfaAppli03][「赤線内にバーコードを配置してください」と表示される][scale=0.3]{
//}

//image[barcode][マネジメントコンソールに表示されたバーコードをスマホで撮る][scale=0.8]{
//}

すると「Google認証システム」のアプリで「start-aws-user」用の認証コード（6桁の数字）が表示（@<img>{mfaAppli04}）されるようになります。

//image[mfaAppli04][「start-aws-user」用の認証コード（6桁の数字）が表示されるようになる][scale=0.3]{
//}

この認証コードは30秒ごとに次々と切り替わっていきます（@<img>{mfaAppli05}）。表示されている認証コードをマネジメントコンソールの「認証コード1」に入力（@<img>{barcode2}）したら切り替わるのを待って、次の認証コードを「認証コード2」に入力します。どちらも入力できたら「仮想MFAの有効化」をクリックしましょう。

//image[mfaAppli05][認証コードは30秒ごとに次々と切り替わる][scale=0.3]{
//}

//image[barcode2][「認証コード1」と「認証コード2」を入力して「仮想MFAの有効化」をクリック][scale=0.8]{
//}

「MFAデバイスは正常に関連付けられました。」と表示（@<img>{barcodeFinish}）されたら「完了」をクリックしてください。

//image[barcodeFinish][「MFAデバイスは正常に関連付けられました。」と表示されたら「完了」をクリック][scale=0.8]{
//}

再び左メニューの「ユーザー」をクリック（@<img>{mfaOn}）してから、右上の更新マークをクリックします。先ほどは「有効でない」になっていたMFAが「仮想」に変わっていたらMFAの設定は完了です。

//image[mfaOn][MFAが「有効でない」から「仮想」に変わっていたらMFAの設定完了][scale=0.8]{
//}

それではMFAを使ったサインインを試してみましょう。右上のIAMユーザー名から「サインアウト」をクリック（@<img>{iamSignOut}）します。

//image[iamSignOut][「サインアウト」をクリック][scale=0.8]{
//}

右上の「コンソールへログイン」をクリック（@<img>{signInToConsole}）します。

//image[signInToConsole][「コンソールへログイン」をクリック][scale=0.8]{
//}

  1. アカウント（12桁の数字）
  2. ユーザー名
  3. パスワード

の3つを入力したら「サインイン」をクリックします。

//image[iamSignInWithMfa][「サインイン」をクリック][scale=0.8]{
//}

今まではこれだけでサインインできていましたが、MFA（多要素認証）が有効になったことで、さらに認証コードも確認されるようになりました。スマホで「Google認証システム」のアプリを起動（@<img>{mfaCode}）して、表示されている認証コードを「MFAコード」（@<img>{signInAgain}）のところへ入力したら「送信」をクリックしてください。

//image[mfaCode][スマホで「Google認証システム」を起動][scale=0.3]{
//}

//image[signInAgain][認証コードを「MFAコード」に入力して「送信」をクリック][scale=0.8]{
//}

マネジメントコンソールが表示されたらMFAを用いたサインインは成功です！今後、サインインするときには必ず「Google認証システム」のアプリが必要になるため、もしIAMユーザのパスワードが盗まれてしまっても、それだけではサインインできないので安心ですね。@<fn>{upgradeMobile}

//footnote[upgradeMobile][スマホを機種変更する際は、MFAが有効なまま旧スマホを処分してしまうとサインイン時にMFAコードが確認できずマネジメントコンソールへ入れなくなってしまいます。機種変更前に一時的にMFAを無効にしておくか、新しいスマホをMFAデバイスとして登録してから旧スマホを処分するようにしましょう。]

機種変更前にMFAの削除を忘れてしまい、MFAが有効な状態で新しい端末にて設定を行おうとすると、当然のことながらログイン時にMFAコードを求められた時に旧端末から呼び出しを行えないと元も子も無くなってしまうので、注意が必要です。

//image[signInFinish][MFAを用いたサインインができるようになった！][scale=0.8]{
//}

=== ルートユーザーもMFAを有効にする

これでIAMユーザーの「start-aws-user」はMFAが有効になりましたが、ルートユーザーはまだMFAが有効になっていません。

いったん「start-aws-user」でサインアウトしたら、今度はルートユーザーでサインインしなおしてください。そしてマネジメントコンソールの「最近アクセスしたサービス」から「IAM」をクリック（@<img>{accessService2}）してIAMのダッシュボードを開きます。

//image[accessService2][ルートユーザーで「最近アクセスしたサービス」から「IAM」をクリック][scale=0.8]{
//}

IAMのダッシュボードで「ルートアカウントのMFAを有効化」（@<img>{rootAccountMfa}）@<fn>{rootAccount}を開いて「MFAの管理」をクリックします。

//footnote[rootAccount][突然「ルートアカウント」という言葉が出てきましたがルートアカウントとルートユーザーは同じものです。他にもサインインとログインで揺れていたりと、AWSでは表記揺れはままあることです。日本語の翻訳がおかしいところもあるので、マネジメントコンソールの言語を英語にした方がいっそ分かりやすいかも知れません。英語が苦手な方は随時脳内補完しながら頑張りましょう。]

//image[rootAccountMfa][「ルートアカウントのMFAを有効化」を開いて「MFAの管理」をクリック][scale=0.8]{
//}

ここからは先ほどと同じ手順でルートユーザーでも仮想MFAを有効にして、サインイン時は「Google認証システム」を使うようにしておいてください。設定完了すると、Google認証システムでもルートユーザー用の認証コード（@<img>{mfaCodeForRoot}）が表示されるようになるはずです。

//image[mfaCodeForRoot][ルートアカウント用の認証コード（6桁の数字）も表示されている][scale=0.3]{
//}

ルートアカウントでもMFAが有効になったら、再び「start-aws-user」でサインインしなおして先へ進みましょう。もしどこのURLからサインインするのか分からなくなってしまったら、先ほど送っておいたメールに「Sign-in URL: https://************.signin.aws.amazon.com/console」というURLがあるはずですので、そこをクリックしてサインインしましょう。MFAコードを聞かれたらスマホのGoogle認証システムを起動して、表示されている6桁の数字を入力します。

== リージョンの変更

再び「start-aws-user」でサインインしなおして、マネジメントコンソールへ戻ってこられましたか？

//image[signInAgainAndAgain][右上に「start-aws-user」「東京」と表示されていたらOK][scale=0.8]{
//}

マネジメントコンソールの右上（@<img>{signInAgainAndAgain}）に表示されているユーザー名が「start-aws-user」であること、そしてその右側に表示されているリージョンが「東京」であることを確認してください。ここがもし「東京」以外になっていたら、クリックして「アジアパシフィック(東京)」を選択（@<img>{selectRegion}）してください。選択後、右上が「東京」に変わったらリージョンの変更は完了です。

//image[selectRegion][「東京」以外のときはクリックして「アジアパシフィック(東京)」を選択][scale=0.8]{
//}

AWSはバージニア、カナダ、ロンドン、シンガポール、東京など世界の各地域にデータセンターを所有しており、@<chapref>{infraAndServer}で詳しくお話ししたようにサーバはそのデータセンターの中にいます。

右上に表示されている「リージョン」とはその各地域の中でどこを使うか？を指定するものです。ウェブサイトにアクセスするとき、パソコンのある場所からサーバまで物理的に距離が遠いと、それだけ通信にも時間がかかって応答時間も遅くなりますので、日本国内向けにウェブサイトを開設する場合は基本的にこの「東京」リージョンを選びましょう。ただしAWSのサービスによって、まだ東京リージョンが使えないものもあります。その場合は次点として「米国東部 (バージニア北部)」を選択してください。@<fn>{northVirginia}

//footnote[northVirginia][「米国東部 (バージニア北部)」はAWSで最初に作られたリージョンで、新しいサービスはまずここのリージョンから提供開始されることが多いためです。ちなみに同じサービスでもリージョンによって料金は少しずつ異なります。]

さらにリージョンという地域ごとの区分の下に、さらにアベイラビリティゾーン@<fn>{az}という区分があります。アベイラビリティゾーンの場所は公開されていませんが、たとえば東京リージョンの下に「池袋アベイラビリティゾーン」と「品川アベイラビリティゾーン」がある、というようなイメージです。

それぞれのアベイラビリティゾーンは異なる場所に存在し、異なる変電所から電力を供給しています。そのため、もし東京リージョン内でどこかのアベイラビリティゾーンが局地的な災害に遭ったとしても、他のアベイラビリティゾーンは問題なく稼動しているので東京リージョン全体が止まってしまうことはありません。

//footnote[az][アベイラビリティゾーンはよくAZと略されます。]

この後、サーバを立てる際に誤って「東京」以外のリージョンでサーバを立てないように注意をしてください。

== CroudTrailでいつ誰が何をしたのか記録

リージョンの確認が済んだら、続いてCloudTrail（クラウドトレイル）を設定へ進みましょう。マネジメントコンソールの左上にある「サービス」から、「管理ツール」の下にある「CloudTrail」（@<img>{selectCloudTrail}）をクリックしてください。

//image[selectCloudTrail][サービス＞管理ツール＞CloudTrail][scale=0.8]{
//}

「CloudTrail」をクリックすると、CloudTrailのダッシュボード（@<img>{cloudTrailDashboard}）が表示されます。CloudTrailはAWSのマネジメントコンソールや、プログラムを通じて行われたAPI呼び出しの履歴を保存してくれるサービス・・・と書くと難しいですが、要は「いつ誰が何をしたのか」を記録しておいてくれるサービスです。

//image[cloudTrailDashboard][CloudTrailダッシュボード][scale=0.8]{
//}

CloudTrailダッシュボードの左メニューにある「イベント履歴」をクリックして、イベントの一覧を確認してみましょう。CloudTrailはデフォルトで有効になっているため、今まで行ってきた「サインイン」や「IAMユーザーの作成」などもすべてイベントとして記録されています。たとえばフィルターを「ユーザー名」にして「start-aws-user」で検索（@<img>{searchCloudTrail}）してみると、いつサインインしたのか、いつMFA（多要素認証）のチェックをしたのか、などが確認できます。@<fn>{utc}

//image[searchCloudTrail][start-aws-userがいつ何をしたのかすべて表示される][scale=0.8]{
//}
//footnote[utc][表示されているイベント時間はUTCですので日本時間とはずれています。]

このようにCloudTrailでは何も設定しなくても、デフォルトで過去90日間@<fn>{addCloudTrail}のイベントが無料で記録されています。今後もし「消した覚えがないのにサーバが跡形もなく消え去っている！」というようなことがあったら、先ずCloudTrailを開いていつ誰がサーバを削除したのか確認してみましょう。

//footnote[addCloudTrail][業務で使うので90日よりももっと前の記録も取っておきたい、という場合は「証跡（しょうせき）の作成」を行ってください。ただし証跡はさかのぼって保存はされないため、何か問題があってから「100日前のイベントが見たい！」と思っても見られません。]

これで「AWSを使い始めたら最初にやるべきこと」はひととおり完了しました。準備万端！それでは次章でサーバを立てていきましょう！