= はじめに

//flushright{

2018年10月
mochikoAsTech

//}

この本を手に取ってくださったあなた、こんにちは、あるいははじめまして。
「AWSをはじめよう」の筆者、mochikoAsTechです。

AWSは好きですか？それとも好きとか嫌いとか言えるほど、AWSのことをまだよく知らない段階ですか？

本著「AWSをはじめよう」ではAWSでサーバを立てたり、そこにWordPressをインストールしたりして、実際にブラウザで自分のサイトが見られるところまで手を動かして実践していきます。

ちなみに本著「AWSをはじめよう」（以下AWS本）は、前作「DNSをはじめよう」（以下DNS本）のストーリーの続きとなっていますので、DNS本を読まずにいきなりAWS本から読むと「上中下巻セットなのに中巻からいきなり読んだ」という感じで色々意味が分からずちょっと戸惑うことになります。

読み進んでいくと第2章辺りで「さてここで事前に下茹でしておいたじゃがいもを取り出します」といわれて「は？下茹でとかいつしてたの？！」という状態になりますので、「DNSは興味ないし面倒くさいんだけど・・・」という方もできればDNS本をお読みいただいて、下ごしらえを済ませた状態でAWS本を開いてみてください。きっとその方が美味しくお召し上がりいただけます。第1章はDNS本を読んでいなくても問題ない内容ですので、とりあえずそのまま読んでいただいても構いません。

AWSの普及によって「アプリケーションエンジニアは開発だけやっていればいい、サーバ周りはインフラエンジニアに任せておけばいい」という完全分業の時代が終わり、今まで聖域化されていたインフラやサーバの世界に、アプリケーションエンジニアやフロントエンドエンジニアも気軽に踏み込めるようになってきました。嫌でも踏み込まざるを得ない時代になってきた、ともいえます。

ですがソースコードを書くアプリケーションエンジニアと違って、インフラエンジニアが実際どんなことをしているのかなんて想像もつかない、「サーバを立てろ」といわれても何をどうしたらいいのか分からない、という人も少なくないのではないでしょうか。

でもインフラってやってみると意外と楽しいんです。そして土台であるインフラを学ぶことで、上もののアプリで頑張っていたことがあっさり解決できる、という場面も結構あったりします。

本著は「AWSやサーバやインフラは怖いものではなくすごく楽しいものなんだよ」ということを、かつての私のような初心者へ伝えたくて書いた一冊です。
読んで試して「面白かった！」と思ってもらえたら、そしてインフラを前より少しでも好きになってもらえたら何より嬉しいです。

== 想定する読者層

本著は、こんな人に向けて書かれています。

  * AWSが何なのかよく分かっていない人
  * ブログやポートフォリオサイトを独自ドメインで作ってみたい人
  * JavaScriptやHTMLやCSSなら書けるけどサーバは分からなくて苦手という人
  * プログラミングの勉強がしたいけど環境構築でつまづいて嫌になってしまった人
  * これからシステムやプログラミングを学ぼうと思っている新人
  * ウェブ系で開発や運用をしているアプリケーションエンジニアの人
  * インフラやサーバになんとなく苦手意識のある人
  * AWS、EC2、RDS、ELB、Auto Scaling、Route53などの単語に興味がある人
  * クラウドってなんだろう？サーバってなんだろう？という人

== 本著の特徴

本著では前作「DNSをはじめよう」で買ったドメインを使って、実際にWordPressで自分のサイトを作ってみます。手を動かしてAWSでサーバを立てたりネットワークの設定をしたりしながら学べるので理解がしやすく、インフラ初心者でも安心して読み進められる内容です。

また実際にありがちなトラブルをとり上げて、

 * 上手くいかないときは原因をどう調べたらいいのか？
 * 見つかった問題をどう解決したらいいのか？
 * 今後、同様の問題はどうしたら事前に避けられるのか？

をコラムやドリルで解説しています。

== 本著のゴール

本著を読み終わると、あなたはこのような状態になっています。

 * WordPressのおしゃれなサイトができあがっている
 * 使うも壊すも自由な勉強用のLinuxサーバ環境が1台手に入る
 * クラウドがなんなのか？や、そのリットデメリットが説明できるようになっている
 * 読む前よりAWSやサーバや黒い画面が怖くなくなっている

== 免責事項

本著に記載されている内容は筆者の所属する組織の公式見解ではありません。

また本著はできるだけ正確を期すように努めましたが、筆者が内容を保証するものではありません。よって本著の記載内容に基づいて読者が行った行為、及び読者が被った損害について筆者は何ら責任を負うものではありません。

不正確あるいは誤認と思われる箇所がありましたら、必要に応じて適宜改訂を行いますのでGitHubのイシューやプルリクエストで筆者までお知らせいただけますと幸いです。

@<href>{https://github.com/mochikoAsTech/startAWS}