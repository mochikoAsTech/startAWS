= AWSでウェブサーバを立てよう

この章では実際にAWSのEC2を使ってウェブサーバを立てます。

//pagebreak

== 事前準備

=== Windowsの場合

Windowsのパソコンを使っている方は、サーバを立てる前に「ターミナル」と呼ばれる黒い画面のソフトをインストールしておきましょう。サーバに接続するときにこのターミナルを使うのですが、ターミナルのソフトには色々な種類があります。

 * RLogin @<href>{http://nanno.dip.jp/softlib/man/rlogin/}
 * Poderosa @<href>{https://ja.poderosa-terminal.com/}
 * Tera Term @<href>{https://ja.osdn.net/projects/ttssh2/}
 * PuTTYjp @<href>{http://hp.vector.co.jp/authors/VA024651/PuTTYkj.html}@<fn>{PuTTYjp}

//footnote[PuTTYjp][PuTTYjpを使う場合、.pemの秘密鍵をPuTTYgenで.ppkに変換する必要が出てきます。他のターミナルソフトに比べると一手間余計にかかるので、特にこだわりがなければRLoginを使用するのがお勧めです。]

//image[rlogin][RLogin][scale=0.8]{
//}

本著ではいちばん上のRLogin（@<img>{rlogin}）を使って説明していきますので、特にこだわりがなければRLoginを使うことをお勧めします。RLoginの「実行プログラム(64bit)」（@<img>{downloadRLogin01}）を@<href>{http://nanno.dip.jp/softlib/program/rlogin_x64.zip}をクリックしてください。

//image[downloadRLogin01][「実行プログラム(64bit)」のURLをクリックしてダウンロード][scale=0.8]{
//}

ダウンロードしたZIPファイルを保存（@<img>{downloadRLogin02}）します。保存場所はどこでも構いませんが、後でどこに置いたか分からなくなりそうな人はデスクトップにしておきましょう。

//image[downloadRLogin02][「ファイルを保存する」でパソコンに保存][scale=0.8]{
//}

デスクトップのZIPファイル（rlogin_x64.zip）を右クリック（@<img>{downloadRLogin03}）して、解凍＞デスクトップに解凍@<fn>{lhaplus}をクリックします。

//image[downloadRLogin03][ZIPファイルを右クリックして解凍＞デスクトップに解凍][scale=0.8]{
//}

//footnote[lhaplus][右クリックしても「解凍」が見当たらないときは、圧縮・解凍の定番ソフトであるLhaplusをインストールしましょう。 @<href>{https://forest.watch.impress.co.jp/library/software/lhaplus/}]

デスクトップにできた「rlogin_x64」というフォルダの中にある「RLogin.exe」@<fn>{filenameExtension}（@<img>{downloadRLogin04}）をダブルクリックすればRLoginが起動（@<img>{downloadRLogin05}）します。

//footnote[filenameExtension][フォルダの中にRLoginはあるけどRLogin.exeなんて見当たらない・・・という場合、ファイルの拡張子が非表示になっています。この後も拡張子を含めてファイル名を確認する場面がでてきますので、「拡張子 表示」でGoogle検索して拡張子が表示されるように設定変更しておきましょう。]

//image[downloadRLogin04][RLogin.exeをダブルクリック][scale=0.8]{
//}

//image[downloadRLogin05][RLoginが起動した][scale=0.8]{
//}

これでRLoginのインストールは完了です。起動したRLoginはいったん閉じてしまって構いません。RLoginは後でまた使いますので、デスクトップの「rlogin_x64」フォルダとその中にある「RLogin.exe」をごみ箱へ捨てないように注意してください。

=== Macの場合

Macを使っている方は、最初から「ターミナル」というソフトがインストールされていますのでそちらを利用しましょう。ターミナルがどこにあるのか分からないときは、Macの画面で右上にある虫眼鏡のマークをクリックして、Spotlightで「ターミナル」と検索すれば起動できます。

以上で事前準備は完了です。お待たせしました。いよいよサーバを立てましょう。

== EC2でサーバを立てる

いよいよサーバを立てましょう。

== SecurityGroup
== VPC
== EC2
=== 請求アラート
=== SSHの鍵認証
=== 鍵の変換
=== ElasticIP
=== Bastion

= サーバのバックアップを取っておこう
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

 AWSについてもっと勉強したい！という場合は、ネットが繋がればどこからでも参加できる「AWS Black Belt Online Seminar」というオンラインセミナーを受けてみましょう。

@<href>{https://aws.amazon.com/jp/about-aws/events/webinars/}

また過去に開催されたオンラインセミナーの資料は「AWSクラウドサービス活用資料集」で公開されています。EC2やELBなどのサービス別に資料が用意されていますので、そちらを読んでみるのもお勧めです。

@<href>{https://aws.amazon.com/jp/aws-jp-introduction/}

== AWS認定資格のクラウドプラクティショナーを目指してみよう

AWSには公式の認定資格（@<img>{AWSCertificationRoadmap}）@<fn>{officialRoadmap}がいくつかあるのですが、その中で最初に挑戦しやすい入門編の認定は「クラウドプラクティショナー」です。

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
