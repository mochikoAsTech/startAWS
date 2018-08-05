= インフラとサーバってなに？

この章ではAWSとはなにか？そもそもクラウドとは何か？サーバとは何か？という基本を学びます。

//pagebreak

== AWSを理解するには先ずインフラを知ろう

AWSとはアマゾン ウェブ サービス（Amazon Web Services）の略で、欲しいものをぽちっとな！すると翌日には届くあのアマゾンがやっているクラウドです。

「AWSはアマゾンがやっているクラウドです」と言われても、「クラウド」が分からないと結局AWSが何なのかよく分からないままですよね。

クラウドって何なのでしょう？

クラウドだけではありません。よくクラウドと一緒に並んでいるサーバやインフラという言葉がありますが、こちらも何だか分かりますか？IT系で働いていても、その辺って「なんか・・・ふんわり・・・なんか雲の向こう側にある・・・ウェブサイト作るための何か・・・？」という程度の認識で、クラウドってなに？とか、サーバってなに？と聞かれたときに、ちゃんと説明できる人は意外と少ないのではと思います。

なので、先ずは「AWSはアマゾンがやっているクラウド」という文章の意味が分かるよう、インフラ周りから順を追って学んでいきましょう。

== インフラとは？

インフラという言葉は知っていますか？

はじめて聞いたという人も、「なんとなくは分かるけど、説明してと言われたらうーん・・・」な人も、いま自分が考える「インフラ」についての説明をここに書いてみましょう。いきなり正解を聞かされるより、自分で答えを考えて書き出してみてからの方が、正解を聞いたときにきっと自分の中へより染み渡ってくるはずです。

//raw[|latex|\begin{reviewimage}\begin{center}\includegraphics[width=1\maxwidth\]{./images/whatIsInfraAnswerSection.png}\end{center}\end{reviewimage}]

では答え合わせをしてみましょう。

インフラとは@<ttb>{サーバやネットワークのこと}です。

そもそもインフラこと「Infrastructure」は、直訳すると基盤や下部構造といった意味です。ですので「生活インフラ」と言うと一般的には上下水道や道路、そしてインターネットなど、生活に欠かすことの出来ない社会基盤のことを指します。

そして技術用語としては、インフラはシステムやサービスの基盤となる「設備」のことをいいます。なので、分かりやすく言うと「インフラとはサーバやネットワークのこと」なのです。

これでもう会社で後輩に「インフラってなんですか？」と聞かれても、堂々と「サーバとかネットワークのことだよ」と答えられますね！

でも後輩に、続けて「え、サーバってなんですか？」と聞かれたらどうしましょう？

== サーバとは？

後輩から「サーバってなんですか？」という直球の質問を投げつけられたら、しっかりホームランで打ち返せますか？

しっかり答えられるか不安な人も、自信のある人も、ちょっと頭の中でサーバの姿を思い浮かべてみてください。できればイラストじゃなくて実写でお願いします。

//comment{
TODO:後でデザイナーさんに依頼↓
//}
//image[imagineServer][サーバの姿を思い浮かべて描いてみよう][scale=0.8]{
//}

思い浮かびますか？あんまり浮かばないですよね。サーバの姿がくっきり思い描ける人の方が少ないのではないかと思います。

でもこれが「パソコンの姿を思い浮かべてください」なら、きっとすぐに浮かんでくるはずです。（@<img>{pcImage}）

//image[pcImage][パソコンの姿ならすぐに思い浮かぶ][scale=0.8]{
//}

でもサーバの姿は？と考えるとなかなか思い浮かびません。

ではサーバの姿をお見せしたいと思います。

=== サーバの姿を見てみよう

//image[HPEProLiantDL360][サーバの姿（HPE ProLiant DL360）][scale=0.8]{
//}

これはHewlett Packard Enterprise（ヒューレット・パッカード エンタープライズ）のHPE ProLiant DL360@<fn>{dl360}というラックマウント型のサーバです。DL360は15年以上前から愛されているシリーズ@<fn>{gen10}で、日本でもっとも売れたラックマウント型のサーバと言っても過言ではないかも知れません。定価で1台おおよそ50万円以上します。

//footnote[dl360][HPE ProLiant DL360 @<href>{https://www.hpe.com/jp/ja/product-catalog/servers/proliant-servers/pip.hpe-proliant-dl360-gen10-server.1010007891.html}]
//footnote[gen10][2018年8月時点で発売されているのはHPE ProLiant DL360 Gen10です。末尾の「Gen10」は世代（Generation）を表しているので、10世代目ということです。]

そして本は本棚に収めるように、サーバはサーバラック（@<img>{serverRack}）@<fn>{HPEAdvancedG2}という専用の棚に収めることが多いです。

//image[serverRack][サーバを収めるためのサーバラック][scale=0.8]{
//}

//footnote[HPEAdvancedG2][写真のサーバラックはHPE Advanced G2シリーズ @<href>{https://www.hpe.com/jp/ja/product-catalog/servers/server-racks/}]

先ほどのHPE ProLiant DL360のようなサーバは、ラック（＝棚）にマウントする（＝乗せる）ことができる形状のため「ラックマウント型サーバ」、略してラックサーバと呼ばれています。

ラックマウント型のサーバは1U（ワンユー）・2U・4Uのように厚みが異なり、1Uならこのサーバラックの1ユニット（1段）分、2Uなら2ユニット（2段）分を使うことになります。そのためラックマウント型サーバは1Uサーバという名前で呼ばれることもあります。サーバラックは42Uサイズが多く、その名前のとおり1Uサーバを42台収めることができます。@<fn>{42u}

//footnote[42u][但しラックに供給される電源の量や放熱の問題もあるため、実際は42Uサイズのラックにサーバ42台をぎちぎちに詰めることは少ないのでは、と思います。]

//image[towerAndBlade][タワー型サーバとブレードサーバ][scale=0.8]{
//}

「ラックマウント型サーバ」だけでなく、デスクトップパソコンのような「タワー型サーバ」（@<img>{towerAndBlade}）@<fn>{tower}や、シャーシやエンクロージャーと呼ばれる箱の中に何本も差し込んで使う省スペースな「ブレードサーバ」@<fn>{blade}など、サーバには色々な形があります。

//footnote[tower][@<href>{https://www.hpe.com/jp/ja/product-catalog/servers/proliant-servers/pip.hpe-proliant-ml110-gen10-server.1010192782.html}]
//footnote[blade][@<href>{https://www.hpe.com/jp/ja/integrated-systems/bladesystem.html}]

こうしたラックマウント型サーバ、タワー型サーバ、ブレードサーバのように、手で触れる実体があるサーバのことを@<ttb>{物理サーバ}といいます。物理的な実態があるから物理サーバです。

そもそもですが、人がウェブサイトを作る時には土台となるサーバが必ず必要となります。たとえはてなブログで無料のブログを作ったときでも、Ameba Owndで無料のホームページを作ったときでも、あなた自身はサーバのことなど気にも留めないと思いますが、どこかしらに必ずそのブログやサイトが乗っかっているサーバは存在しています。

ではサーバはいったいどこにいるのでしょう？

=== サーバはデータセンターにいる

前述のサーバラックや、その中に詰まったラックサーバを実際に見たことはありますか？

どんなウェブサイトも、世界中のどこかにあるサーバの中で稼動しているはずなのですが、インフラエンジニアでなければサーバを見る機会はなかなかないかも知れません。

サーバはほとんどの場合、@<ttb>{データセンター}と呼ばれる場所に設置されています。@<fn>{serverRoom}

//footnote[serverRoom][企業によっては、オフィス内にサーバルームがあってサーバはそこにいるかも知れません。]

カラオケをするには防音や音響設備の整ったカラオケルームが適しているように、サーバを動かすためのさまざまな設備が整った場所のことをデータセンター、略してDC@<fn>{dataCenter}といいます。先ほどのラックサーバがたくさん並んでいますね。（@<img>{dc}}）

//footnote[dataCenter][データセンター（Data Center）の頭文字を取ってDCですが、その中でもインターネット用途向けのデータセンターはインターネットデータセンター、略してiDCと呼ばれたりします。「逆にインターネット用途以外のデータセンターってなに？」となりますが、メインフレーム（インターネット以前の時代の大型コンピュータ）向けということのようです。]

//image[dc][データセンターはサーバのための設備が整っている][scale=0.8]{
//}

しかし「サーバを動かすための設備」と言われても、「電源取れればそれでいいんじゃないの？専用の建物なんか要る？」と思われるかも知れません。サーバを動かすのに適した設備とはどんなものなのでしょう？

==== 〈サーバに適した設備〉1.防犯設備

もし悪い誰かが「この企業が気に食わないから商品のウェブサイトを落としてやろう」と思ったとき、あるいは「このネットショップの顧客情報を根こそぎ盗んでやろう」と思ったとき、ネット越しにサイトを攻撃したり侵入したりするだけでなく、そのサイトが動いているサーバのところまで行って物理的に破壊したり、ハードディスクを引っこ抜いて盗んだり、という手段があります。

//comment{
TODO:後でデザイナーさんに依頼↓
//}
//image[attack][攻撃や窃盗はインターネット越しでも物理的にでもできる][scale=0.8]{
//}

データセンターは後者の「物理的な攻撃や侵入」からサーバを守るための設備を整えています。

堅牢さはデータセンターによって異なりますが、たとえば次のような防犯対策が取られています。

 * 所在地を一般に公開しない@<fn>{address}
 * 建物自体に侵入経路となる窓がない
 * 事前予約をした上で顔写真つきの身分証を提示しないと建物に入れない
 * エントランスで空港と同じような手荷物チェックや金属探知機チェック、静脈認証がある
 * 上着や荷物、携帯電話、カメラなどは持ち込み禁止
 * 借りているサーバラックがある階にしかエレベータが止まらない
 * サーバルームへの入退室は監視カメラと静脈認証で記録
 * 入るときと出るときで体重が違うと出られない

//footnote[address][2018年7月、都内で建築現場の火災が発生した際に「この建物はAWSのデータセンターとして建築していた可能性が高い」というニュースが出ており、断定はしていなかったものの「それは報道していいの？周知の事実になってしまったら、もう一度同じ場所に立てるの無理なのでは・・・？」とちょっと気になりました。]

また「うちは弱小サイトだから誰かのうらみも買わないし、盗まれるような個人情報もないよ」という場合でも、防犯だけでなく天災や熱の対策も必要です。

==== 〈サーバに適した設備〉2.地震・火事対策設備

ウェブサイトはサーバ上で稼動しているため、サーバが止まればもちろんサイトも見られなくなってしまいます。@<fn>{stopServer}

//footnote[stopServer][冗談のようですが「こちらのサーバを停止して削除しますね」「はい、使ってないのでいいです」という会話をした後で、実際にサーバを削除したら「サイトが見られなくなったんですけど！」という連絡が来た、という話も聞きます。サーバがなければサイトは見られない、というのは決して万人にとって当たり前のことではないのです。]

もし地震などの天災があったときにも絶対にサーバを止めないため、データーセンターの建物は耐震構造になっていることはもちろん、次のような電力供給対策もされています。

 * 変電所から電力を受ける受電設備は複数用意して冗長化している
 * もし停電があっても電力が途絶えないよう、電力は複数の変電所から引いている
 * 両方の変電所が止まって完全に電力が途絶えたらUPS（無停電電源装置）が自動稼働
 * さらに数十秒以内に自家発電機が稼動し、最低数日間は追加の燃料給油なしで稼動可能
 * 燃料（重油やジェット燃料）は販売元業者と有事の優先供給の契約をしており、供給が続く限りは自家発電で稼動し続けることが可能

電源がなくなればパソコンも落ちてしまうように、サーバも、その上で稼動しているウェブサイトも、電力が供給されなければ落ちてしまいます。仮にサーバを2台用意して「1台壊れても、もう1台でサイトは見られる！大丈夫！」と安心していても、データセンターの電力そのものが止まってしまえば、どちらのサーバも電源が切れてサイトは見られなくなります。電気は使えて当たり前と思いがちですが、311の輪番停電のように「当たり前が崩れたとき」にも、いつもどおり稼動できる環境がデータセンターには求められているのです。

さらに万が一火事が起きても、サーバにじゃんじゃん水をかけて消火するわけにはいきません。火は酸素をエネルギーにして燃えるので、多くのデータセンターでは酸素以外のガスで部屋を満たして消火するガス消火設備を備えています。

==== 〈サーバに適した設備〉3.空調設備

そして一生懸命稼動しているサーバはとても熱くなります。皆さんのパソコンにもファンなどの冷却機構が付いていて、使っていると熱を冷まそうとしますよね。サーバも同じで、たくさんのサーバが詰まったサーバラックの裏側には、熱い空気がいっぱい吐き出されてきます。

暑い部屋ではサーバが故障したり落ちてしまったりする@<fn>{summerWars}ため、データセンター内のサーバルームの空調はとても強く、人間が過ごすにはちょっとつらい寒さです。

//footnote[summerWars][アニメ映画のサマーウォーズで、冷却用の氷が部屋からなくなったことでスーパーコンピュータが熱暴走し、主人公が大事なゲームに負けてしまうシーンを思い出してください。]

このように防犯、地震・火事対策、空調といった設備が整ったデータセンターで、サーバは日々元気に稼動しているのです。

=== 物理サーバと仮想サーバ

部屋を借りるとき、「1DKの部屋なら12万、2LDKの部屋なら20万」のように広いほうが家賃は高くなります。データセンターを借りるときもまったく同じで「1/2ラックなら12万、1ラックまるごとなら20万」のように、ラックサイズによって月額の費用が変わってきます。

そして2LDKの部屋に1人で住むと、1人で20万負担しなければなりませんが、シェアハウスにして10人で住めば1人当たりの家賃コストは2万円に下がります。

サーバラックも同様に、42Uのラックに1Uサーバを1台しか乗せないより、42台詰め込んだ方が1台当たりのコストは下がります。

2000年代前半、インターネットが盛り上がってきてサーバがどんどん必要になってきた頃、42Uのラックになんとかもっとたくさんのサーバを詰め込めないか？と試行錯誤した結果、前述の省スペースなブレードサーバや、1Uの半分サイズで奥と手前に2台収納できる1Uハーフサイズのサーバなどが台頭してきました。

しかし1つのラックに割り当てられた電源の量には上限があるため、42Uにぎちぎちに詰め込むと今度は電源が足りなくなってしまいます。@<fn>{power}データセンターによっては、電源容量を増やせるオプションを提供しているところもありますが、それはそれで「10A増やしたら3万円」のように月額費用に跳ね返ってきます。

//footnote[power][ぎちぎちに詰め込んでなんとか稼動していたものの、ある日データセンターで停電が起きて全台停止。電源はすぐに復旧して自動で全台いっせいに起動しようとしたが、サーバは起動時がいちばん電源を食うため、ラックのブレーカーが落ちて再度全台停止。いっせいに起動しようとしてはブレーカーが落ちて全台停止、をずっと繰り返していた・・・という怪談を聞いたことがあります。本当に怖い話ですね。]

ラックのスペースは決まっている、使える電源の容量も決まっている。でもそこに置けるサーバの台数を増やしたい！そこで「物理サーバのサイズを小さくする」とは別のアプローチで生まれてきたのが@<ttb>{仮想サーバ}です。

@<ttb>{物理サーバが一軒家だとすれば、仮想サーバはマンション}（@<img>{houseAndMansion}）です。

//comment{
TODO:後でデザイナーさんに依頼↓
2つは同じサイズにして欲しい
//}
//image[houseAndMansion][物理サーバは一軒家、仮想サーバはマンション][scale=0.8]{
//}

一軒家には1世帯しか住めません@<fn>{house}}が、マンションにすれば土地のサイズは同じままで10世帯住むことができます。1台の物理サーバをそのまま使うのではなく、物理サーバ上に何台もの仮想サーバを作ることで、サーバラックのサイズはそのままでサーバ台数を増やすことができたのです。

//footnote[house][一軒家で2世帯同居だってあるでしょ！みたいな突っ込みは心にしまってください。]

このときマンションの建物にあたる物理サーバを@<ttb>{ホストサーバ}、101号室や201号室のような各部屋にあたる仮想サーバを@<ttb>{ゲストサーバ}と呼んだりします@<fn>{hostServer}。

//footnote[hostServer][ホストOS、ゲストOSという呼び方をすることもあります。]

物理的な実体があるのが物理サーバですが、その逆で手で触れる物理的な実態がないのが仮想サーバです。手で触れられるのはあくまでホストOSのサーバであり、ゲストOSのサーバはその中で仮想的にしか存在しないため、手で触ることはできません。

同じ広さのラックスペースに、いままでよりたくさんのサーバが詰め込めるなんて仮想サーバ素晴らしい！と思いますが、一軒家よりマンションの方が建築コストが高いのと同じで、仮想サーバを立てるにはホストサーバとなる物理サーバのスペックも高くなければならないため、初期投資額がぐっと高くなります。

データセンターで借りるラックスペース代も高いし、物理サーバだって何十万もします。スペースを切り詰めるために仮想サーバにしたいと思っても、ホストサーバとなる物理サーバはスペックが高いのでさらに高額・・・となると中小企業やスタートアップ企業が自社で物理サーバや仮想サーバを所有・管理するのはなかなか大変なことです。

そこで資本力のある会社が大きなホストサーバをたくさん立てて、その上の仮想サーバ（ゲストサーバ）を他の人に貸すような仕組みが生まれました。

お分かりでしょうか？勘のいい方はもうお気づきのことと思いますが、ここでようやく「クラウドとは何か？」という話と繋がってきます。

== オンプレミスとクラウド

昔々は、企業が「そろそろ自社のウェブサイト作りたいなぁ・・・だからサーバが必要だ！」と思ったら、「サーバを買う」という選択肢しかありませんでした。

サーバを買うと言っても、お店に行ってぱっと買って持ち帰れる、という訳ではありません。

「どのメーカーのサーバにしよう？EHPかな？それともIBMかな？DELLがいいかな？」と各社の見積もりをとり、値引き交渉をして、それでも数十万から数百万するので社内の稟議を通してやっと購入。購入してもすぐ届くわけではなく、数週間待ってやっと届きます。そして届いたらサーバを段ボールから出して、データセンターもしくは自社のサーバルームにあるサーバラックのところまで持って行って、がっちゃんこと設置。設置できたら今度は同じく自前のネットワーク機器からLANケーブルを繋ぎ、電源も繋ぎます。そしてOSのインストールディスクを用意したらサーバにOSをインストールして・・・以下省略しますが、要は「ただ自社のウェブサイトが作りたいだけなのに、サーバを用意するのがすごく大変だった」ということです。

自分でサーバを買って、何もかも自分で用意しないといけないため、
 * 初期投資のサーバ代が高い
 * サーバを置くのに適した場所も必要
 * 「欲しい！」と思ってから使い始めるまでに時間がかかる
という状況でした。このようにインフラを自前で用意して、自社で所有・管理するのがいわゆる@<ttb>{オンプレミス}です。

これに対してクラウドは、オンプレミスと違ってサーバを買うのではなく、サービスとして「使う」だけです。

クラウドなら「自社のウェブサイト作りたいなぁ・・・だからサーバが必要だ！」と思ったら、ブラウザを開いて、クラウド事業者のサイト上で使いたいサーバのスペックを選んでぽちっとなするだけで、すぐにサーバを立てることができます。しかもAWSなら課金も1秒単位の従量課金なので、たとえばサーバを5分使ったら5分ぶんの費用しかかかりません。こんな簡単にサーバを使い始めたりやめたりできるのは、クラウド事業者が物理サーバそのものを提供しているのではなく、大きなホストサーバをたくさん用意しておいて、その上に立てた仮想サーバ（ゲストサーバ）を提供しているからです。

オンプレミスはサーバを買って使う、クラウドはサービスとして使う、ということですね。でもまだちょっとわかりにくいと思うので、お店を例にオンプレミスとクラウドの違いを確認してみましょう。

=== クラウドのメリットとデメリット

たとえば私が突然ピザ作りに目覚めて、もうインフラエンジニアなんかやってる場合じゃない！ピザ屋を始めるんだ！@<fn>{pizza}と思い立ったとします。

//footnote[pizza][そしたら「AWSをはじめよう」の続編として「ピザ屋をはじめよう」という本が書けますね。]

ピザ屋さんをオープンすべく、土地を買って、そこに店舗となる建物を建てて、電気とガスと水道を通して、床板や壁紙を貼って・・・からやると、お金も場所も時間もたくさん必要です。しかも準備が整ってやっとオープンしたと思ったら、たった1か月で資金が足りなくなってお店がつぶれることになったとしても、今度は建物の取り壊しや土地の処分など、止めるときは止めるときでやることがたくさんあります。このように全部自分で買って、自分で所有・管理するオンプレミスだと、「ちょっと気軽にピザ屋さんをやってみよう」はなかなか厳しいことが分かります。

一方クラウドは、フードコートへの出店に似ています。「ピザ屋をはじめたい！だからフードコートの一区画を借りてやってみよう！」という感じです。

これだと建物はもうあって、電気ガス水道ももう用意されています。フードコート内の一区画を契約して使わせてもらうだけなので、すべて自分で準備するオンプレミスと違ってすぐに始められます。しかも数か月やってみて「もうピザ焼くの飽きたわー！」と思ったら、その区画を借りるのを止めるだけでいいのです。前述のとおりAWSなら使い始めるときの初期費用もなく1秒単位の従量課金なので「ピザ屋さんもうやめたいけど、この先30年のローン支払いが残ってるからやめるにやめられない・・」ということもありません。「前月の25日までに契約終了を申し出る必要がある」といった制限すらないので、本当にいつでもやめられます。

クラウドならとても簡単に出店できる（つまりサーバを用意できる）ので、私は本来やりたかった「美味しいピザを焼いて売る」（ウェブサイトを作って自社を宣伝する）という本業に注力できます。

さらに、もしピザ屋さんが大繁盛したら、フードコート内で自店の隣の区画も借りて、お店を広くすることも簡単にできるので、初めから広い区画を借りておく必要もありません。つまり、ウェブサイトへのアクセスが増えてきてサーバのスペックが足りなくなったら、後から増強したり好きなだけサーバの台数を増やしたりもできるので、最初から高スペックなサーバを借りておく必要がありません。

クラウドなら初期投資額が少なく、すぐに始められて、すぐにやめられる。よく「クラウドはスモールスタートに向いている」と言われますが、その理由はまさにこういうところにあるのです。

但し、長い目で見るとフードコートにテナント料を払い続ける方が、土地や建物を買うよりも最終的には高くなるかも知れません。前述のとおり初期投資は少なくて済むのですが、クラウドのいいところは、決して「コストが安くなる」ということではありません。実際、AWSは他社の共有レンタルサーバやVPS@<fn>{vps}と比べると高額です。

//footnote[vps][Virtual Private Serverの略。先ほど出てきた仮想サーバのことだと思ってください。]

クラウドのよいところは、たとえばショッピングセンター内でフードコートが入っている南館が地震で崩れてしまっても、すぐに北館に移ってピザ屋の営業を再開できる、といった冗長性です。

この冗長性を自力で確保しようとしたら大変です。ピザ屋さんを常に営業し続けておくために、いつ来るか分からない地震に備えて最初から予備の店舗も確保しておかなければならないとしたら、相当なコストがかかります。オンプレミスのサーバなら、ただ自社サイトを作りたいだけなのに、品川と渋谷の2か所でデータセンターを借りて両方に1台ずつホストサーバを用意しておき、品川のデータセンターが使えなくなったらその上で動いていたゲストサーバを渋谷のホストサーバに移動させる、というような大仰な話です。これを勝手にやってくれるクラウドはすごいですよね。

ここまでクラウドの良さを色々お話ししてきましたが、もちろんデメリットもあります。

もし何かトラブルがあってフードコート全体がお休みになるときは、問答無用でピザ屋さんもお休みになってしまいます。つまり使っているクラウドで大規模障害が起きたら、一利用者である私たちにできることはなく復旧までひたすら待つしかない、ということです。AWSでも広範囲にわたる障害は定期的に起きています。たとえば2016年には豪雨による電源障害でサーバに接続できなくなる事象が発生@<fn>{awsTrouble}しました。こうした障害の際も、AWSが発表してくれる内容がすべてですので、原因が分かるまで自分で徹底的に調べる、あるいは自力で何とかする、ということはできません。

//footnote[awsTrouble][Amazonクラウドのシドニーリージョン、豪雨による電源障害でEC2などに一部障害。現在は復旧 － Publickey @<href>{https://www.publickey1.jp/blog/16/amazonec2.html}]

また通路やトイレ、駐車場といった共有スペースはフードコート内の他店舗（ドーナツ屋さんやラーメン屋さんなど）と共有していますので、フードコート内で他のお店が混んでくると、駐車場が満杯になってピザ屋さんに来たかったお客さんが入れなかったり、人波が自分の店の方まで押し寄せてきたりとマイナスな影響も受けます。つまり同じクラウド@<fn>{sameCloud}を使っているウェブサイトにアクセスが集中すると、たとえば回線がひっ迫したりして自分のサイトまで繋がりにくくなる、ということです。

//footnote[sameCloud][具体的には、同じホストサーバを使っている他のゲストサーバ上のサイト。あるいは同じインターネット回線を使っている他のサーバ上のサイト、ということです。]

=== AWSはAmazonがやっているクラウド

たくさんお話ししてきたので、一度おさらいをしましょう。

企業が「自社のウェブサイト作りたいなぁ・・・だからサーバが必要だ！」と思ったとき、自分でサーバを買って自分で管理しなければいけないのがオンプレミスです。そして「自社のウェブサイト作りたいなぁ・・・だからサーバが必要だ！」と思ったとき、従量課金ですぐ使えて、性能や台数の増減も簡単にできるのがクラウドです。

そしてようやく最初の話に戻ると、AWSとはアマゾン ウェブ サービス（Amazon Web Services）の略で、欲しいものをぽちっとな！すると翌日には届くあのAmazonがやっているクラウドです。

AWSがなんなのか、お分かりいただけましたでしょうか？

=== パブリッククラウドとプライベートクラウド

ところでパブリッククラウドやプライベートクラウド、という言葉は聞いたことがありますか？

AWSのようなクラウドは、パブリッククラウドと呼ばれることもあります。みんなでホストサーバという資源（リソース）を共有して使うので、「公共の」という意味の「パブリック」が付いています。

クラウドが少しずつ使われるようになった頃に「クラウドって便利そうだけど、みんなで共有するのってちょっと抵抗あるな・・・」と思った人たちを安心させるため、「プライベートクラウド」という言葉が生まれました。プライベートクラウドとはいったい何なのでしょう？

たとえばオンプレミスの環境で「高スペックな物理サーバを買ってホストサーバにして、その上でゲストサーバ（仮想サーバ）を立てられるようにしたぞ！ホストサーバのスペックが足りる限りという制限はあるものの、好きなときに好きなだけゲストサーバを立てたり、増強したりできるのでこれはクラウド！プライベートなクラウドだ！」と言うこともできます。また「クラウド事業者が提供しているホストサーバを1台まるまる占有する契約をしたぞ！自社で物理サーバを所有している訳ではないのでこれはクラウドだ。しかも他の人はこのホストサーバ上のゲストサーバを使えないから、プライベートなクラウドだ！」と言うこともできます。定義は曖昧なのですが、このように@<ttb>{みんなで共有せず、自社だけで専有できるクラウドをプライベートクラウドと呼ぶ}ようです。

このプライベートクラウドだと「初期投資額が少ない」「サーバの性能や台数を後から好きなだけ増強できる」といった、クラウド本来のメリットが享受できないように思えますが、これもクラウドなのでしょうか？

このようにクラウドという言葉はとても曖昧です。結局「クラウド」という言葉の定義がはっきりしていないため、その人が言っている「クラウド」という言葉がなにを指しているのかは、よくよく聞いてみないと分からない、ということです。@<fn>{whatIsCloud}

//footnote[whatIsCloud][実際、オンプレミス環境にある仮想サーバをクラウドサーバと呼んでいるケースも多々あります。]

=== AWS以外のクラウド

ところでクラウドはAWS以外にもGoogleのGoogle Cloud Platform@<fn>{gcp}、MicrosoftのAzure（アジュール）@<fn>{azure}、その他にも国内クラウドとしてさくらインターネットがやっているさくらのクラウド@<fn>{sakura}、GMOクラウド@<fn>{gmoCloud}などたくさんあります。

//footnote[gcp][@<href>{https://cloud.google.com/}]
//footnote[azure][@<href>{https://azure.microsoft.com/ja-jp/}]
//footnote[sakura][@<href>{https://cloud.sakura.ad.jp/}]
//footnote[gmoCloud][@<href>{https://www.gmocloud.com/}]

その中でもなぜAWSなのでしょう？

2018年時点、クラウド市場ではAWSがシェア33%でトップを独走中@<fn>{cloudShare}です。そのため他のクラウドと比べて、使ったことがあって対応可能なエンジニアも多いし、何か困ったときに調べて出てくる情報も多い、というのが、私がAWSを選ぶいちばんの理由です。それ以外だと、利益が出た分だけどんどん投資されてサービスが改良されていくため、細かな使い勝手がどんどん良くなっていく@<fn>{improve}ところもポイントです。

//footnote[cloudShare][2018年第1四半期、クラウドインフラ市場でAWSのシェアは揺るがず33％前後、マイクロソフト、Googleが追撃、IBMは苦戦中。Synergy Research － Publickey @<href>{https://www.publickey1.jp/blog/18/20181aws33googleibmsynergy_research.html}]
//footnote[improve][画面や機能もどんどん変わっていくので、この後出てくる設定画面も皆さんが手を動かしてやってみる頃にはキャプチャと違っているかも知れません。AWSのいいところでもあり、マニュアルなどを作って説明する側にとってはつらいところでもあります。]

クラウドを選ぶ理由、その中でもAWSを選ぶ理由というのは、普遍的な何かがあるわけではなく、本来は使う人やその上で動かすサイトによって異なるはずです。あなたが動かしたいサイトによっては、AWSではなく他のVPSの方がいいケースだってもちろんあるはずです。これから使ってみて、あなた自身がAWSの良いところを発見できたらいいですね。

=== 【ドリル】サンプル

==== 問題

問題問題

 * A. Route53
 * B. お名前.com

//raw[|latex|\begin{reviewimage}\begin{flushright}\includegraphics[width=0.5\maxwidth\]{./images/answerColumnShort.png}\end{flushright}\end{reviewimage}]

==== 解答

正解はBです。

= AWSとは？
== AWSは最初の1年無料
=== 無料枠に含まれるもの
=== 無料の1年が終わる前にすべきこと

= AWSでウェブサーバを立てよう
== マネジメントコンソール
== IAM
== 請求アラート
== リージョン
== CroudTrail
== SecurityGroup
== VPC
== EC2
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