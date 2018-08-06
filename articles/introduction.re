= はじめに

//flushright{

2018年10月
mochikoAsTech

//}

この本を手に取ってくださったあなた、こんにちは、あるいははじめまして。
「AWSをはじめよう」の筆者、mochikoAsTechです。

前作の「DNSをはじめよう」では、お名前.comでドメインを買って、AWSのアカウントを作り、Route53をネームサーバとして使うところまでをやってみました。
そして本著「AWSをはじめよう」では、そのそのドメインを使って自分のサイトを作ってみます。

AWSでウェブサーバを立てたり、DBサーバを立てたり、WordPressをインストールしたりして、ブラウザで自分のサイトが見られるところまで一緒に頑張ってやっていきましょう！

え、この本って別の本の続きなの？そっちを先に読んだ方がいい？と思ったあなた、ぜひ「DNSをはじめよう」を先に読んでください。

ケーキのデコレーションはスポンジを焼いてからでないと出来ないように、いきなり「AWSをはじめよう」から読み始めると「え、これを先にやっておかなきゃだったの？」「なにこれ、こんなの用意してない」となってさまざまな手戻りが発生します。はじめようシリーズ1作目となる「DNSをはじめよう」を読んでから、「AWSをはじめよう」を読み始めることを強くお勧めします。

== 想定する読者層

本著は、こんな人に向けて書かれています。

  * AWSがなんなのかよく分かっていない人
  * ブログやポートフォリオサイトを独自ドメインで作ってみたい人
  * JavaScriptやHTMLやCSSなら書けるけどサーバは分からなくて苦手という人
  * プログラミングの勉強がしたいけど環境構築でつまづいて嫌になってしまった人
  * これからシステムやプログラミングを学ぼうと思っている新人
  * ウェブ系で開発や運用をしているアプリケーションエンジニア
  * インフラやサーバになんとなく苦手意識のある人
  * AWS、EC2、RDS、ELB、Auto Scaling、IAM、CloudTrail、Route53などの単語に興味がある人
  * クラウドってなんだろう？サーバってなんだろう？という初心者

== 本著の特徴

本著では前作「DNSをはじめよう」で買ったドメインを使って、実際にWordPressで自分のサイトを作ってみます。手を動かしてAWSでサーバを立てたりロードバランサーの設定をしたりしながら学べるので理解がしやすく、インフラ初心者でも安心して読み進められる内容です。

また実際にありがちなトラブルをとり上げて、

 * 上手くいかないときは原因をどう調べたらいいのか？
 * 問題をどう解決したらいいのか？
 * どうしたら事前に避けられるのか？

を解説するとともに、実際にコマンドを叩いて反復学習するためのドリルもついています。

== 本著のゴール

本著を読み終わると、あなたはこのような状態になっています。

 * WordPressのおしゃれなサイトができあがっている
 * 使うも壊すも自由な勉強用のLinuxサーバ環境が1台手に入る
 * 物理サーバと仮想サーバの違いが説明できるようになっている
 * オンプレミスとクラウド、それぞれのメリットデメリットが分かるようになっている
 * 読む前よりAWSやサーバや黒い画面が怖くなくなっている

== 免責事項

本著に記載されている内容は筆者の所属する組織の公式見解ではありません。

また本著はできるだけ正確を期すように努めましたが、筆者が内容を保証するものではありません。よって本著の記載内容に基づいて読者が行った行為、及び読者が被った損害について筆者は何ら責任を負うものではありません。

不正確あるいは誤認と思われる箇所がありましたら、電子版については必要に応じて適宜改訂を行いますので筆者までお知らせいただけますと幸いです。
