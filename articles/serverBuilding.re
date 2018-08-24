= AWSでウェブサーバを立てよう

この章では実際にAWSのEC2を使ってウェブサーバを立てます。

//pagebreak

== 事前準備

=== お使いのパソコンがWindowsの場合

Windowsのパソコンを使っている方は、サーバを立てる前に「ターミナル」と呼ばれる黒い画面のソフトをインストールしておきましょう。サーバに接続するときにこのターミナルを使うのですが、ターミナルのソフトには色々な種類があります。

 * RLogin（@<href>{http://nanno.dip.jp/softlib/man/rlogin/}）
 * Poderosa（@<href>{https://ja.poderosa-terminal.com/}）
 * Tera Term（@<href>{https://ja.osdn.net/projects/ttssh2/}）
 * PuTTYjp（@<href>{http://hp.vector.co.jp/authors/VA024651/PuTTYkj.html}）@<fn>{PuTTYjp}

//footnote[PuTTYjp][PuTTYjpを使う場合、.pemの秘密鍵をPuTTYgenで.ppkに変換する必要が出てきます。他のターミナルソフトに比べると一手間余計にかかるので、特にこだわりがなければRLoginを使用するのがお勧めです。]

//image[rlogin][RLogin][scale=0.8]{
//}

本著ではいちばん上のRLogin（@<img>{rlogin}）を使って説明していきますので、特にこだわりがなければRLoginを使うことをお勧めします。RLoginの「実行プログラム(64bit)@<fn>{64bit}」（@<img>{downloadRLogin01}）のURL、@<href>{http://nanno.dip.jp/softlib/program/rlogin_x64.zip}をクリックしてください。

//footnote[64bit][もしパソコンのWindowsが32bit版だった場合は「実行プログラム(32bit)」のURLをクリックしてください。]

//image[downloadRLogin01][「実行プログラム(64bit)」のURLをクリックしてダウンロード][scale=0.8]{
//}

ダウンロードしたZIPファイルを保存（@<img>{downloadRLogin02}）します。保存場所はどこでも構いませんが、後でどこに置いたか分からなくなりそうな人はデスクトップに保存しておきましょう。

//image[downloadRLogin02][「ファイルを保存する」でパソコンに保存][scale=0.8]{
//}

デスクトップのZIPファイル（rlogin_x64.zip）を右クリック（@<img>{downloadRLogin03}）して、解凍＞デスクトップに解凍@<fn>{lhaplus}をクリックします。

//image[downloadRLogin03][ZIPファイルを右クリックして解凍＞デスクトップに解凍][scale=0.8]{
//}

//footnote[lhaplus][右クリックしても「解凍」が見当たらないときは、圧縮・解凍の定番ソフトであるLhaplusをインストールしましょう。 @<href>{https://forest.watch.impress.co.jp/library/software/lhaplus/}]

解凍したら、デスクトップにできた「rlogin_x64」というフォルダの中にある「RLogin.exe」@<fn>{filenameExtension}（@<img>{downloadRLogin04}）をダブルクリックすればRLoginが起動（@<img>{downloadRLogin05}）します。

//footnote[filenameExtension][フォルダの中にRLoginはあるけどRLogin.exeなんて見当たらない・・・という場合、ファイルの拡張子が非表示になっています。この後も拡張子を含めてファイル名を確認する場面がでてきますので、「拡張子 表示」でGoogle検索して拡張子が表示されるように設定変更しておきましょう。]

//image[downloadRLogin04][RLogin.exeをダブルクリック][scale=0.8]{
//}

//image[downloadRLogin05][RLoginが起動した][scale=0.8]{
//}

これでRLoginのインストールは完了です。起動したRLoginはいったん閉じてしまって構いません。また後で使いますので、デスクトップの「rlogin_x64」フォルダとその中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。

=== お使いのパソコンがMacの場合

Macを使っている方は、最初から「ターミナル」というソフトがインストールされていますのでそちらを利用しましょう。ターミナルがどこにあるのか分からないときは、Macの画面で右上にある虫眼鏡のマークをクリックして、Spotlightで「ターミナル」と検索すれば起動できます。

以上で事前準備は完了です。お待たせしました。いよいよサーバを立てましょう。

== EC2でウェブサーバを立てる

AWSにはRoute53のようなネームサーバをはじめとして色々なサービスがありますが、サーバはAmazon Elastic Compute Cloudの略で「EC2」（イーシーツー）と呼ばれています。

ちなみにAWSではサーバのことを、@<ttb>{インスタンス}と呼びます。ここから先でインスタンスと書いてあったらサーバのことだと思ってください。

それではマネジメントコンソールの左上にある「サービス」から、「コンピューティング」の下にある「EC2」（@<img>{selectEC2}）をクリックしてください。

//image[selectEC2][サービス＞コンピューティング＞EC2][scale=0.8]{
//}

「EC2」をクリックすると、EC2のダッシュボード（@<img>{EC2Dashboard}）が表示されます。「注意: インスタンスは アジアパシフィック (東京) リージョンで作成されます」と書いてあることを確認したら、中央にある「インスタンスの作成」をクリックしてください。

//image[EC2Dashboard][EC2ダッシュボードで「インスタンスの作成」をクリック][scale=0.8]{
//}

ここから7つのステップでインスタンスを作成していきます。

=== ステップ 1: Amazon マシンイメージ (AMI)

はじめにAmazonマシンイメージ、略してAMIを選択します。AMIはこれから作るサーバのもととなるテンプレートのようなものです。

左側の「無料利用枠のみ」にチェックを入れる（@<img>{ec2Step01}）と、無料利用枠以外のAMIは選択できなくなります。うっかりWindows Serverのような有料AMIを選択しないようにチェックを入れておきましょう。

//image[ec2Step01][「無料利用枠のみ」にチェックを入れて「Amazon Linux AMI」を選択][scale=0.8]{
//}

パソコンにはOSという基本ソフトが入っていて、WordやExcel、ChromeといったソフトはそのOSの上で動いています。皆さんのパソコンにも「Windows 10」や「Mac OS X Lion」などのOSが入っていますよね。

そしてパソコンと同じようにサーバにも「Linux」や「Windows Server」といったサーバ用のOSがあります。サーバを立てるときにはLinuxを選択することが多いのですが、このLinuxの中にもさらに「RHEL（Red Hat Enterprise Linux）」や「CentOS」、「Ubuntu」などいろいろなディストリビューション（種類）があります。

今回は上から2つめにある「Amazon Linux」のAMIを選択します。Amazon LinuxならAWSのツールがあらかじめ入っており、AmazonによるOSのサポートも受けられる@<fn>{osSupport}ため、AWSでサーバを立てるときはOSはAmazon Linuxにすることをお勧めします。Amazon LinuxはRed Hat系のディストリビューションですので、Red HatやCentOSのサーバを使ったことがある方なら違和感なく使えると思います。

//footnote[osSupport][AmazonによるOSのサポートというのは「手取り足取り教えてくれる」ということではなく、たとえば「バグや脆弱性が発見されたときに修正バージョンを出してくれる」というものです。サポートの期限はAmazon Linuxが2020年6月30日まで、Amazon Linux 2が2023年6月30日まで、と公式に発表されています。 @<href>{https://aws.amazon.com/jp/amazon-linux-2/faqs/}]

Amazon Linuxには2018年8月時点で

 * Amazon Linux
 * Amazon Linux 2

の2種類があります。Amazon LinuxはRHEL6系なのでCentOS 6、Amazon Linux 2はRHEL7系なのでCentOS 7と使い勝手はほぼ同じです。本著ではAmazon Linuxを選択します。@<fn>{apache}

//footnote[apache][ちなみにこの後インストールするApacheというミドルウェアはAmazon Linuxだと2.2系、Amazon Linux 2だと2.4系になります。]

=== ステップ 2: インスタンスタイプの選択

ステップ2ではインスタンスタイプを選択（@<img>{ec2Step01}）します。テスト環境にはT2インスタンス、データベースやキャッシュを処理させるならM5インスタンス、というように用途別にたくさん用意されているので、その中から適したスペックのインスタンスタイプを選びます。

//image[ec2Step02][「無料利用枠のみ」にチェックを入れて「Amazon Linux AMI」を選択][scale=0.8]{
//}

インスタンスタイプの接頭辞になっている「T2」や「M4」はインスタンスファミリーと呼ばれるグループを表しており、Tが開発・検証用、Mが汎用、CがCPU重視、Rはメモリ重視、のように特徴ごとに分かれています。文字の後ろの2や4といった数字は世代を表しているので、T2なら開発・検証向けのグループで2世代目ということですね。Tは3世代目となるT3もリリースされたので、2018年8月時点ではT2とT3がどちらも選択できる状態になっています。

インスタンスファミリーの後ろにあるnano、micro、small、medium、large、xlargeなどはCPUやメモリといったスペックの大きさを表します。t2.smallならCPU@<fn>{vCPU}が1コアでメモリが2GiB、t2.mediumならCPUは2コアでメモリが4GiBというように、大きくなるにつれて段々CPUやメモリが増えていきます。@<fn>{potato}

//footnote[vCPU][インスタンスタイプの表ではCPUが「vCPU」と書かれていると思います。仮想サーバ内にある仮想のCPUのことをVirtual CPU、略してvCPUといいます。]

//footnote[potato][S→M→Lと段々量が増えていくなんてマクドナルドのポテトと同じですね。]

今回は個人で「ちょっとWordPressのサイトを作ってみよう！」という用途なので高スペックは必要ありません。無料利用枠の対象となっているt2.microを選択して「次の手順: インスタンスの詳細の設定」をクリックします。

===[column] 【コラム】T2系バーストモードの落とし穴

T2系のインスタンスタイプには落とし穴があるので注意が必要です。

たとえば先ほど選択したt2.microというインスタンスタイプはCPUが1コアと書いてありますが、実際はベースラインという「普段はここまで使っていいよ」というラインがあり、サイトにあまりアクセスが来ておらずサーバがヒマなとき、vCPUの使用率がこのベースラインを下回っていれば「CPUクレジット」というものがちゃりんちゃりんと貯まっていきます。@<fn>{baseLine}CPUクレジットはt2.microなら1時間あたり6ずつ溜まっていって最大で144まで蓄積できます。

//footnote[baseLine][@<href>{https://docs.aws.amazon.com/ja_jp/AWSEC2/latest/UserGuide/t2-credits-baseline-concepts.html}]

前述のベースラインですがt2.microだとなんとたったの10%です。普段はvCPUを1コアの1/10しか使えない、ということです。そしてサイトにアクセスがわーっと殺到してCPU使用率がベースラインの10%を超えるとバーストモードになり、バーストモードの間だけはvCPUが100%使えるようになります。

バーストモードの間は今まで貯めておいたCPUクレジットを使います。1クレジットにつき1分間バーストできるので、t2.microなら最大で144分しかバーストできません。つまりCPU使用率が10%を超える状態が2時間半続いたら、その時点でバーストが終了して強制的にまたvCPUが10%までしか使えなくなってしまうのです。

アクセスが殺到していたからvCPUを10%以上使っていたわけで、それが急に10%までしか使えなくなってしまったらどうなるのでしょう？バーストが終了した瞬間にサーバは過負荷となり、場合によってはサイトが応答できなくなってしまいます。

つまり今までオンプレミスでCPUが1コアのサーバを使っていてそれがちょうどよかったからといって、AWSでt2.microを選ぶとベースラインが10%なのでvCPUは実質0.1しかないため、AWSに引越しした途端サイトが落ちまくって「同じスペックを選んだはずなのにどうして？！」という事態になる可能性があるということです。

CPUクレジットが尽きたら追加課金でバーストモードを延長できるT2 Unlimitedというオプションもありますが、Unlimitedで延々課金されるくらいならもう少し上のインスタンスタイプを選んでベースラインを超えないようにしましょう。ちなみに3世代目のT3系はこのUnlimitedがデフォルトで有効になっているので「なーんだ、t3.microでも結構アクセスさばけるじゃん！」と思っていると、実はUnlimitedで延々課金されていた！となる初心者殺しな仕様といえます。

===[/column]

=== ステップ 3: インスタンスの詳細の設定

=== ステップ 4: ストレージの追加

=== ステップ 5: タグの追加

=== ステップ 6: セキュリティグループの設定

=== ステップ 7: インスタンス作成の確認

== SecurityGroup
== VPC
== EC2
=== 請求アラート
=== SSHの鍵認証
=== 鍵の変換
=== ElasticIP
=== Bastion

= サーバのバックアップを取っておこう
== スナップショット
== AMI

= ELBでバランシングやサーバの台数を管理しよう
== ELB
== Auto Scaling
=== スケーリングに使える
=== サーバが1台死んでも自動で1台立ち上がる

= DBサーバを立てよう
== RDS
== Amazon Aurora

= ネームサーバの設定をしよう
== Route53

= もっとAWSについて勉強したい！

== 公式のオンラインセミナーや資料集

 AWSについてもっと勉強したい！という場合は、ネットに繋がればどこからでも参加できる「AWS Black Belt Online Seminar」というオンラインセミナーを受けてみましょう。

@<href>{https://aws.amazon.com/jp/about-aws/events/webinars/}

過去に開催されたオンラインセミナーの資料は「AWSクラウドサービス活用資料集」で公開されています。EC2やELBなどのサービス別に資料が用意されていますので、そちらを読んでみるのもお勧めです。

@<href>{https://aws.amazon.com/jp/aws-jp-introduction/}

== AWS認定資格のクラウドプラクティショナーを目指してみよう

AWSには公式の認定資格（@<img>{AWSCertificationRoadmap}）@<fn>{officialRoadmap}がいくつかあるのですが、その中で最初に挑戦しやすい入門者向けの認定資格は「クラウドプラクティショナー」です。

//image[AWSCertificationRoadmap][AWS認定資格のロードマップ][scale=0.8]{
//}

//footnote[officialRoadmap][AWS認定より引用。 @<href>{https://aws.amazon.com/jp/certification/}]

認定資格に挑戦することでAWSの主要なサービスやセキュリティの基本、料金体系などをまんべんなく学ぶことができます。本著を読んで「もっとAWSについて勉強したいな！」と思ったらチャレンジしてみてはいかがでしょうか？

= AWSをやめたくなったらすること
== 無料の1年が終わる前にすべきこと

=== 【ドリル】サンプル

==== 問題

問題問題

 * A. Route53
 * B. お名前.com

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。
