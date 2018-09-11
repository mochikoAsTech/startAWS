= インフラとサーバってなに？

この章ではAWSとはなにか？そもそもクラウドとは何か？サーバとは何か？という基本を学びます。

//pagebreak

== AWSを理解するには先ずインフラを知ろう

AWSとはAmazon Web Services（アマゾン ウェブ サービス）の略で、欲しいものをぽちっとな！すると翌日には届くあのAmazonがやっているクラウドです。

「AWSはAmazonがやっているクラウドです」と言われても、「クラウド」が分からないと結局AWSが何なのかよく分からないままですよね。

クラウドって何なのでしょう？

クラウドだけではありません。よくクラウドと一緒に並んでいるサーバやインフラという言葉がありますが、こちらも何だか分かりますか？IT系で働いていても、その辺って「なんか・・・ふんわり・・・なんか雲の向こう側にある・・・ウェブサイト作るための何か・・・？」という程度の認識で、クラウドってなに？とか、サーバってなに？と聞かれたときに、ちゃんと説明できる人は意外と少ないのではと思います。

なので、先ずは「AWSはAmazonがやっているクラウド」という文章の意味が分かるよう、インフラ周りから順を追って学んでいきましょう。

== インフラとは？

インフラという言葉は知っていますか？

初めて聞いたという人も、「なんとなくは分かるけど、説明してと言われたらうーん・・・」な人も、いま自分が考える「インフラ」についての説明をここに書いてみましょう。いきなり正解を聞かされるより、自分で答えを考えて書き出してみてからの方が、正解を聞いたときにきっと自分の中へより染み渡ってくるはずです。

//raw[|latex|\begin{reviewimage}\begin{center}\includegraphics[width=1\maxwidth\]{./images/whatIsInfraAnswerSection.png}\end{center}\end{reviewimage}]

では答え合わせをしてみましょう。

インフラとは@<ttb>{サーバやネットワークのこと}です。

そもそもインフラこと「Infrastructure」は、直訳すると基盤や下部構造といった意味です。ですので「生活インフラ」と言うと一般的には上下水道や道路、そしてインターネットなど生活に欠かすことの出来ない社会基盤のことを指します。

そして技術用語としては、インフラはシステムやサービスの基盤となる「設備」のことを指します。なので、分かりやすく言うと「@<ttb>{インフラとはサーバやネットワークのこと}」なのです。

これでもう会社で後輩に「インフラってなんですか？」と聞かれても、堂々と「サーバとかネットワークのことだよ」と答えられますね！

でも後輩に、続けて「え、サーバってなんですか？」と聞かれたらどうしましょう？

== サーバとは？

IT系、その中でも特にウェブ業界で働いている人にとってサーバは身近な存在です。業務上でテストサーバや本番サーバ、ウェブサーバやデータベースサーバなどの単語を見聞きすることはよくあると思います。また日常生活でも「テレビで紹介されたらアクセスが殺到してサーバが落ちたんだって」とか「ソシャゲのアプリで遊ぼうとしたのにサーバが重くてなかなか遊べない」というように普通に使われます。

でももし後輩から「サーバってなんですか？」という直球の質問を投げつけられたら、しっかりホームランで打ち返せますか？

サーバっていったい何なのでしょう？

サーバとは@<ttb>{クライアントに対してサービスを提供するもの}です。でも「サービスを提供するもの」と言われても、ちょっとふんわりした表現すぎて分かりにくいので具体例を出しましょう。

サーバと名の付くもののひとつにビアサーバがあります。

前述の「サーバとはクライアントに対してサービスを提供するものである」という文章を、ビアサーバに当てはめてみましょう。「@<ttb>{ビアサーバとは客に対してビールを提供するものである}」（@<img>{beerServerAndWebServer}）、さっきまで分かりにくかった文章もビアサーバを当てはめたら急に分かりやすくなりましたね。

//image[beerServerAndWebServer][ビアサーバもウェブサーバもクライアントに対してサービスを提供するものである][scale=0.8]{
//}

それではビアサーバと同じようにウェブサーバも前述の文章に当てはめてみましょう。「@<ttb>{ウェブサーバとは、客に対してウェブページを提供するものである}」、こちらも具体的になってとても分かりやすいですね。

ビアサーバに対して「ビールをください」というリクエストを投げると、つまりビアサーバのコックを「開」の方へひねると、ビールというレスポンスが返ってきます。そしてウェブサーバに対して「ウェブページを見せてください」というリクエストを投げれば、ウェブページというレスポンスが返ってきます。

つまりビアサーバもウェブサーバも、その本質は「Server」の直訳である「給仕人」なので、繰り返しになりますがサーバとは@<ttb>{クライアントに対してサービスを提供するもの}なのです。

ところでちょっと頭の中でサーバの姿を思い浮かべてみてください。できればイラストじゃなくて実写でお願いします。思い描いたサーバの姿を「？」が浮かんでいるもやもやの中に描いてみましょう。

//image[imagineServer][サーバの姿を実写で思い浮かべて描いてみよう][scale=0.8]{
//}

サーバの姿を思い浮かべて絵は描けましたか？あんまりくっきりとは浮かばないですよね。サーバの姿なんて明確に思い描ける人の方が少ないのではないかと思います。

でもこれが「パソコンの姿を思い浮かべてください」なら、きっとすぐに浮かんでくるはずです。（@<img>{pcImage}）

//image[pcImage][パソコンの姿ならすぐに思い浮かぶ][scale=0.8]{
//}

でもサーバの姿は？と考えると、パソコンのときとは打って変わってなかなか思い浮かびません。

では皆さんを悩ませるサーバの姿をお見せしたいと思います。

=== サーバの姿を見てみよう

//image[HPEProLiantDL360][サーバの姿（HPE ProLiant DL360）][scale=0.8]{
//}

じゃじゃーん！これがサーバの姿です！

これはHewlett Packard Enterprise（ヒューレット・パッカード エンタープライズ）が出しているHPE ProLiant DL360@<fn>{dl360}というラックマウント型のサーバです。DL360は15年以上前から愛されているシリーズ@<fn>{gen10}で、日本でもっとも売れたラックマウント型のサーバと言っても過言ではないかも知れません。1台につき定価でおおよそ50万円以上します。

//footnote[dl360][HPE ProLiant DL360 @<href>{https://www.hpe.com/jp/ja/product-catalog/servers/proliant-servers/pip.hpe-proliant-dl360-gen10-server.1010007891.html}]
//footnote[gen10][ちなみに2018年8月時点で発売されているのはHPE ProLiant DL360 Gen10です。末尾の「Gen10」は世代（Generation）を表しているので、10世代目ということです。]

そして本を本棚に収めるように、サーバはサーバラック（@<img>{serverRack}）@<fn>{HPEAdvancedG2}という専用の棚に収めることが多いです。

//image[serverRack][サーバを収めるためのサーバラック][scale=0.8]{
//}

//footnote[HPEAdvancedG2][写真のサーバラックはHPE Advanced G2シリーズ @<href>{https://www.hpe.com/jp/ja/product-catalog/servers/server-racks/}]

先ほどのHPE ProLiant DL360のようなサーバは、このラック（＝棚）にマウントする（＝乗せる）ことができる形状のため「@<ttb>{ラックマウント型サーバ}」、略してラックサーバと呼ばれています。

ラックマウント型のサーバは1U（ワンユー）@<fn>{1u}・2U・4Uのように厚みが異なり、1Uのサーバならこのサーバラックの1ユニット（1段）分、2Uのサーバなら2ユニット（2段）分を使うことになります。そのためラックマウント型サーバは1Uサーバという名前で呼ばれることもあります。サーバラックは42Uサイズが多く、その名前のとおり1Uサーバを42台収めることができます。@<fn>{42u}

//footnote[1u][1Uの厚みは1.75インチ（44.45mm）です。]
//footnote[42u][但しラックに供給される電源の量や放熱の問題もあるため、実際は42Uサイズのラックにサーバ42台をぎちぎちに詰めるとは限りません。]

//image[towerAndBlade][タワー型サーバとブレードサーバ][scale=0.8]{
//}

「ラックマウント型サーバ」だけでなく、デスクトップパソコンのような形状の「タワー型サーバ」（@<img>{towerAndBlade}）@<fn>{tower}や、シャーシやエンクロージャーと呼ばれる箱の中にサーバを何台も差し込んで使う省スペースな「ブレードサーバ」@<fn>{blade}など、サーバには色々な形があります。

//footnote[tower][@<href>{https://www.hpe.com/jp/ja/product-catalog/servers/proliant-servers/pip.hpe-proliant-ml110-gen10-server.1010192782.html}]
//footnote[blade][@<href>{https://www.hpe.com/jp/ja/integrated-systems/bladesystem.html}]

そしてこうしたラックマウント型サーバ、タワー型サーバ、ブレードサーバのように、@<ttb>{手で触れる実体があるサーバを物理サーバ}といいます。物理的な実体があるから物理サーバです。（この「物理サーバ」という言葉は後でまた出てきますので覚えておいてください）

そもそもですがウェブサイトを作る時には土台となるサーバが必ず必要となります。たとえはてなブログで無料のブログを作ったときでも、Ameba Owndで無料のホームページを作ったときでも、あなた自身はサーバのことなど気にも留めないと思いますが、どこかしらに必ずそのブログやサイトが乗っかっているサーバは存在しています。

ではそれらの@<ttb>{サーバはいったいどこにいる}のでしょう？

=== サーバはデータセンターにいる

サーバラックや、その中に詰まったラックマウント型サーバを実際に見たことはありますか？

どんなウェブサイトも、世界中のどこかにあるサーバの中で稼動しているはずなのですが、インフラエンジニアでなければサーバを見る機会はなかなかないかも知れません。

サーバはほとんどの場合、@<ttb>{データセンター}と呼ばれる場所に設置されています。@<fn>{serverRoom}

//footnote[serverRoom][企業によっては、オフィス内にサーバルームがあってサーバはそこに設置されているかも知れません。趣味で自宅にサーバを置いている人もいますね。]

カラオケをするには防音や音響設備の整ったカラオケルームが適しているように、サーバを動かすために必要な設備が整った場所のことをデータセンター、略してDC@<fn>{dataCenter}といいます。先ほどのラックサーバがたくさん並んでいますね。（@<img>{dc}）

//footnote[dataCenter][データセンター（Data Center）の頭文字を取ってDCですが、その中でもインターネット用途向けのデータセンターはインターネットデータセンター、略してiDCと呼ばれたりします。「逆にインターネット用途以外のデータセンターってなに？」となりますが、メインフレーム（インターネット以前の時代の大型コンピュータ）向けのデータセンターということのようです。]

//image[dc][データセンターにはサーバのための設備が整っている][scale=0.8]{
//}

しかし「サーバを動かすための設備」と言われても、「電源取れればそれでいいんじゃないの？専用の建物なんか要る？」と思われるかも知れません。サーバを動かすのに適した設備とはどんなものなのでしょう？

==== 〈サーバに適した設備〉1.防犯設備

もし悪い誰かが「この企業が気に食わないから商品のウェブサイトを落としてやろう」と思ったとき、あるいは「このネットショップの顧客情報を根こそぎ盗んでやろう」と思ったとき、ネット越しにサイトを攻撃したり侵入したりするだけでなくそのサイトが動いているサーバのところまで行って物理的に破壊したり、ハードディスクを引っこ抜いて盗んだり、という手段があります。

//image[attack][攻撃や窃盗はインターネット越しでも直接でもできる][scale=0.8]{
//}

データセンターは後者の「物理的な攻撃や侵入」からサーバを守るための設備を整えています。堅牢さはデータセンターによって異なりますが、たとえば次のような防犯対策が取られています。

 * 所在地を一般に公開しない@<fn>{address}
 * 建物自体に侵入経路となる窓がない
 * 厳重な警備体制
 * 事前予約をした上で顔写真つきの身分証を提示しないと建物に入れない
 * エントランスで空港と同じような手荷物チェックや金属探知機チェックがある
 * 上着や荷物、携帯電話、カメラなどは持ち込み禁止
 * 借りているサーバラックがある階にしかエレベータが止まらない
 * サーバルームへの入退室は監視カメラと生体認証で記録
 * 入るときと出るときで体重が違うと出られない

//footnote[address][2018年7月、都内で建築現場の火災が発生した際に「この建物はAWSのデータセンターとして建築していた可能性が高い」というニュースが出ており、断定はしていなかったものの「それは報道していいの？周知の事実になってしまったら、もう一度同じ場所に立てるの無理なのでは・・・？」とちょっと心配になりました。]

入退出時の体重チェックは健康のためではなく、盗んだハードディスクを持ち出せないようにするためです。また「うちは弱小サイトだから誰かのうらみも買わないし、盗まれるような個人情報もないよ」という場合でも、防犯だけでなく天災や熱の対策も必要です。

==== 〈サーバに適した設備〉2.地震・火事対策設備

ウェブサイトはサーバ上で稼動しているため、サーバが止まればもちろんサイトも見られなくなってしまいます。@<fn>{stopServer}

//footnote[stopServer][冗談のようですが「こちらのサーバを停止して削除しますね」「はい、使ってないのでいいです」というやり取りをした後で、実際にサーバを削除したら「サイトが見られなくなったんですけど！」という問い合わせが来た、という話も聞きます。サーバがなければサイトは見られない、というのは決して万人にとって当たり前のことではないのです・・・・ないのです・・・・。]

もし地震などの天災があったときにも絶対にサーバを止めないため、データセンターの建物は耐震や免震構造になっていることはもちろん、次のような電力供給対策もされています。

 * 変電所から電力を受ける受電設備は複数用意して冗長化している
 * もし停電があっても電力が途絶えないよう、電力は複数の変電所から引いている
 * 万が一完全に電力が途絶えたら即座にUPS（無停電電源装置）が起動
 * さらに数分以内に自家発電機が稼動し、最低数日間は追加の燃料給油なしで稼動可能
 * 燃料（重油やジェット燃料）は販売元業者と有事の優先供給の契約をしており、供給が続く限りは自家発電で稼動し続けることが可能

電源がなくなればパソコンも落ちてしまうように、サーバもその上で稼動しているウェブサイトも電力が供給されなければ落ちてしまいます。仮にサーバを2台用意して「1台壊れても、もう1台があれば大丈夫！」という冗長構成にしていても、データセンターの電力そのものが止まってしまえばどちらのサーバも電源が切れてサイトは見られなくなります。電気は使えて当たり前と思いがちですが、東日本大震災後の輪番停電のように「当たり前が崩れたとき」にもいつもどおり稼動できる環境がデータセンターには求められているのです。@<fn>{hokkaido}

//footnote[hokkaido][2018年9月に北海道の胆振地方で震度7の地震が発生して道内のほぼ全域が停電してしまったとき、さくらインターネットの石狩データセンターはUPSと自家発電で稼動を続けました。筆者が使っている「さくらのVPS」というサーバも石狩DCにありましたが止まることなく動き続けていて、普段から「こういうとき」のために備えていたんだなと涙が出そうな気持ちになりました。一部電源切替がうまくいかなかったUPSが原因で数時間停止したサービスもあったそうですが、それでも事業と地震の規模を考えると本当に頭が下がります。ありがとう、さくらインターネット！]

さらに万が一火事が起きても、サーバにじゃんじゃん水をかけて消火するわけにはいきません。火は酸素をエネルギーにして燃えるので、多くのデータセンターでは不燃性のガスで部屋を満たして消火するガス消火設備を備えています。

==== 〈サーバに適した設備〉3.空調設備

そして一生懸命稼動しているサーバはとても熱くなります。皆さんのパソコンにもファンなどの冷却機構が付いていて、使っていると自分自身の熱を冷まそうとしますよね。サーバも同じで、たくさんのサーバが詰まったサーバラックの裏側には熱い空気がいっぱい吐き出されてきます。

暑い部屋ではサーバが故障したり落ちてしまったりする@<fn>{summerWars}ため、データセンター内のサーバルームの空調はとても強く、人間が過ごすにはちょっとつらい寒さです。

//footnote[summerWars][アニメ映画の「サマーウォーズ」で、冷却用の氷が部屋からなくなったことでスーパーコンピュータが熱暴走し、主人公が大事なゲームに負けてしまうシーンを思い出してください。]

このように防犯、地震・火事対策、空調といった設備が整ったデータセンターで、サーバは日々元気に稼動しているのです。

以上、@<ttb>{サーバはいったいどこにいるの？}というお話でした。

=== 物理サーバと仮想サーバ

ところで部屋を借りるときは「1DKの部屋なら8万円、2LDKの部屋なら12万円」のように広いほうが家賃は高くなりますよね。データセンターを借りるときもまったく同じで「ラックの1/2なら12万円、1ラックまるごとなら20万円」のように、ラックサイズによって月額の費用が変わってきます。

そして2LDKの部屋に1人で住むと、1人で20万円負担しなければなりませんが、シェアハウスにして2人で住めば1人当たりの家賃コストは10万円に下がります。サーバラックも同様で、42Uのラックに1Uサーバを1台しか乗せないより42台詰め込んだ方が1台当たりのラック使用コストは下がります。

2000年代前半、インターネットが盛り上がってきてサーバがどんどん必要になってきた頃、42Uのラックになんとかもっとたくさんのサーバを詰め込めないか？と各社が試行錯誤した結果、前述の省スペースなブレードサーバや、奥行きが1Uの半分サイズで奥と手前に2台収納できる1Uハーフサイズのサーバなどが台頭してきました。

しかし1つのラックに割り当てられた電源の量には上限があるため、42Uにサーバをぎちぎちに詰め込むと今度は電源が足りなくなってしまいます。@<fn>{power}データセンターによっては、電源容量を増やせるオプションを提供しているところもありますが、それはそれで「10A増やしたら3万円」のように月額費用に跳ね返ってきます。

//footnote[power][ぎちぎちに詰め込んでなんとか稼動していたものの、ある日データセンターで停電が起きて全台停止。電源はすぐに復旧して自動で全台一斉に起動しようとしたが、サーバは起動時がいちばん電源を食うためラックのブレーカーが落ちて再度全台停止。一斉に起動しようとしてはブレーカーが落ちて全台停止、を延々と繰り返していた・・・という怪談を聞いたことがあります。本当に怖い話ですね。]

ラックのスペースは決まっている、使える電源の容量も決まっている。でもそこに置けるサーバの台数を増やしたい！そこで「物理サーバのサイズを小さくする」とは別のアプローチで生まれてきたのが@<ttb>{仮想サーバ}です。

@<ttb>{物理サーバが一軒家だとすれば、仮想サーバはマンション}（@<img>{houseAndMansion}）です。

//image[houseAndMansion][物理サーバは一軒家、仮想サーバはマンション][scale=0.8]{
//}

一軒家には基本的に1世帯しか住めません@<fn>{house}が、マンションにすれば土地のサイズは同じままで10世帯住むことができます。1台の物理サーバをそのまま使うのではなく、物理サーバ上に何台ものバーチャル（仮想的）なサーバを作ることで、サーバラックのサイズはそのままで論理的なサーバ台数を増やすことができたのです。

//footnote[house][一軒家で2世帯同居だってあるでしょ！という突っ込みは心にしまってください。]

このとき@<ttb>{マンションの建物にあたる物理サーバをホストサーバ}、101号室や201号室のような@<ttb>{各部屋にあたる仮想サーバをゲストサーバ}と呼んだりします@<fn>{hostServer}。

//footnote[hostServer][ホストOS、ゲストOSという呼び方をすることもあります。]

前述のとおり物理的な実体があるのが物理サーバですが、その逆で@<ttb>{手で触れる物理的な実体がないのが仮想サーバ}です。手で触れられるのはあくまでホストサーバであり、ゲストサーバはその中で仮想的にしか存在しないため手で触ることはできません。

同じ広さのラックスペースに、今までよりたくさんのサーバが詰め込めるなんて仮想サーバ素晴らしい！と思いますが、一軒家よりマンションの方が建築コストが高いのと同じで、仮想サーバを立てるにはホストサーバとなる物理サーバのスペックも高くなければならないため、初期投資額がぐっと高くなります。

データセンターで借りるラックスペース代も高いし、物理サーバだって何十万もします。スペースを切り詰めるために仮想サーバにしたいと思っても、ホストサーバとなる物理サーバはスペックが高いのでさらに高額・・・となると中小企業やスタートアップ企業が自社で物理サーバや仮想サーバを所有・管理するのはなかなか大変なことです。

そこで資本力のある会社が大きなホストサーバをたくさん立てて、その上の仮想サーバ（ゲストサーバ）を他の人に貸すような仕組みが生まれました。

長々と物理サーバと仮想サーバについて説明してきましたが、なんとなくゴールがお分かりでしょうか？勘のいい方はもうお気づきのことと思いますが、ここでようやく「@<ttb>{クラウドとは何か？}」という話と繋がってきます。

== オンプレミスとクラウド

=== オンプレミスとは？

昔々は、企業が「そろそろ自社のウェブサイト作りたいなぁ・・・だからサーバが必要だ！」と思ったら、「サーバを買う」という選択肢しかありませんでした。しかしサーバを買うと言っても、お店に行ってぱっと買って持ち帰れるという訳ではありません。

「どのメーカーのサーバにしよう？HPEかな？それともIBMかな？DELLがいいかな？」と各社の見積もりを販社経由で取り、値引き交渉をして、それでも数十万から数百万するので社内の稟議を通してやっと購入。購入してもすぐ届くわけではなく、数週間待ってやっと届きます。そして届いたらサーバを段ボールから出して、データセンターもしくは自社のサーバルームにあるサーバラックのところまで持って行って、がっちゃんこと設置。@<fn>{kitting}

//footnote[kitting][昨今はあまり聞かない単語ですが、サーバを箱から出してセットアップする一連の作業を「キッティング」といいます。]

設置できたら今度は同じく自前のネットワーク機器からLANケーブルを繋ぎ、電源も繋ぎます。そしてOSのインストールディスクを用意してサーバにOSをインストールして・・・以下省略しますが、要は「@<ttb>{ただ自社のウェブサイトが作りたいだけなのにサーバを用意するまでがすごく大変だった}」ということです。

自分でサーバを買って、何もかも自分で用意しないといけないため、

 * 初期投資のサーバ代が高い
 * サーバを置くのに適した場所も必要
 * 「欲しい！」と思ってから使い始めるまでに時間がかかる

という状況でした。このようにインフラを自前で用意して、自社で所有・管理するのがいわゆる@<ttb>{オンプレミス}です。

=== クラウドとは？

これに対してクラウドは、オンプレミスと違ってサーバを買うのではなく、サービスとして「使う」だけです。

クラウドなら「自社のウェブサイト作りたいなぁ・・・だからサーバが必要だ！」と思ったら、ブラウザを開いてクラウド事業者のサイト上で使いたいサーバのスペックを選んでぽちっとなするだけで、すぐにサーバを立てることができます。しかもAmazonのクラウドことAWSなら課金も1秒単位の従量課金なので、たとえばサーバを5分使ったら5分ぶんの費用しかかかりません。こんな簡単にサーバを使い始めたりやめたりできるのは、クラウド事業者が物理サーバそのものを提供しているのではなく、性能のいいホストサーバをたくさん用意しておいて、その上に立てた仮想サーバ（ゲストサーバ）を提供しているからです。

@<ttb>{オンプレミスはサーバを買って使う、クラウドはサービスとして使う}ということですね。でもまだちょっとわかりにくいと思うので、お店を例にオンプレミスとクラウドの違いをもう少し確認してみましょう。

=== クラウドのメリットとデメリット

たとえば私が突然ピザ作りに目覚めて「もうインフラエンジニアなんかやってる場合じゃない！ピザ屋を始めるんだ！」@<fn>{pizza}と思い立ったとします。

//footnote[pizza][そうしたら「AWSをはじめよう」の続編として「ピザ屋をはじめよう」という本が書けますね。]

ピザ屋をオープンすべく、土地を買ってそこに店舗となる建物を建て、電気とガスと水道を通して、床板や壁紙を貼って・・・からやると、お金も場所も時間もたくさん必要です。しかも準備が整ってやっとオープンしたと思ったら、たった1か月で資金が足りなくなってお店がつぶれることになったとしても、今度は建物の取り壊しや土地の処分など、止めるときは止めるときでやることがたくさんあります。このように全部自分で買って、自分で所有・管理するオンプレミスだと、「ちょっと気軽にピザ屋をはじめてみよう」はなかなか厳しいことが分かります。

一方クラウドは、フードコートへの出店に似ています。「ピザ屋をはじめたい！だからフードコートの一区画を借りてやってみよう！」という感じです。

これだと建物はもうあって、電気ガス水道も用意されています。フードコート内の一区画を契約して使わせてもらうだけなので、すべて自分で準備するオンプレミスと違ってすぐに始められます。しかも数か月やってみて「もうピザ焼くの飽きたー！」と思ったら、その区画を借りるのを止めるだけでいいのです。前述のとおりAWSなら使い始めるときの初期費用もなく1秒単位の従量課金なので「ピザ屋もうやめたいけど、この先30年のローン支払いが残ってるからやめるにやめられない・・」ということもありません。「前月の25日までに契約終了を申し出る必要がある」といった制限すらないので、本当にいつでもやめられます。@<fn>{foodcourt}

//footnote[foodcourt][とはいえ現実のフードコートで出店する場合は契約期間の縛りがあるでしょうし、止めようと思っても即日でやめられるものではないですよね。実はEC2の料金体系も従量課金の「オンデマンド」の他に「リザーブドインスタンス」といって長期利用が確約できれば料金が最大75%も安くなるプランがあります。つまり「僕と契約して低コストになってよ！」ということなので途中解約ができないリスクがあることは認識した上で利用しましょう。]

クラウドならとても簡単に出店できる（つまり簡単にサーバを用意できる）ので、私は本来やりたかった「美味しいピザを焼いて売る」（ウェブサイトを作って自社を宣伝する）という本業に注力できます。

さらに、もしピザ屋が大繁盛したら、フードコート内で自店の隣の区画も借りてお店を広くすることも簡単にできるので、初めから広い区画を借りておく必要もありません。つまり、ウェブサイトへのアクセスが増えてきてサーバのスペックが足りなくなったら、@<ttb>{後からサーバを増強したり好きなだけサーバの台数を増やしたりもできる}ので、最初から高スペックなサーバを借りておく必要がないということです。

クラウドなら初期投資額が少なく、すぐにはじめられてすぐにやめられる。よく「クラウドはスモールスタートに向いている」と言われますが、その理由はまさにこういうところにあるのです。

一方でオンプレミスにもメリットはあります。自分が夢見るピザ屋のイメージに合わせて好きな広さや造りの建物を設計するところから始めるので、フードコートとは違って自由度がとても高くなります。たとえばクラウドならメニューにあるサーバから選ぶことしかできませんが、オンプレミスなら「CPUは最小限でいいけどメモリとハードディスクはめいっぱい積みたい」といったように、サービスに最適なサーバをこだわって作れる、ということです。

またサーバを購入して所有していれば会社の資産となりますが、クラウドの場合はどれだけ長く使ってもサーバは自社のものにはなりません。あくまで借りているだけです。会計の視点から見るとオンプレミスの場合はサーバ代は固定費となるため先々の見通しもつけやすいですが、クラウドの場合は使った分だけの変動費となるため費用の予測はあくまで予測となります。

さらに長い目で見るとフードコートにテナント料を払い続ける方が、土地や建物を買うよりも最終的には高くなるかも知れません。前述のとおり初期投資は少なくて済むのですが、クラウドのいいところは決して「コストが安くなる」ということではありません。実際、AWSは他社の共有レンタルサーバやVPS@<fn>{vps}と比べると高額です。

//footnote[vps][Virtual Private Serverの略。先ほど出てきた仮想サーバのことだと思ってください。]

クラウドのよいところは、前述のすぐに始められてすぐにやめられる初期コストの低さ。それからショッピングセンター内でフードコートが入っている南館が火災で倒壊してしまっても、すぐに北館に移ってピザ屋の営業を再開できる、といった可用性です。

この可用性を自力で確保しようとしたら大変です。ピザ屋を常に営業し続けておくために、いつ来るか分からない火災に備えて最初から予備の店舗も確保しておかなければならないとしたら相当なコストがかかります。オンプレミスに当てはめて考えると、ただ自社サイトを作りたいだけなのに品川と渋谷の2か所でデータセンターを借りて両方に1台ずつサーバを用意しておき、もし品川のデータセンターが火災で使えなくなっても渋谷のデータセンターにあるサーバは生きているのでサイトは見られる、というような構成にしておかなければななりません。予見できない災害に対してどこまで冗長性を確保@<fn>{dr}しておくのか？はシステムの重要性とコストのバランスによります。このような構成が手間も費用も低コストで実現できるクラウドはすごいですよね。

//footnote[dr][このように火事や自然災害などが起きてもサービスが止まらないように備えておく体制をディザスタリカバリ（Disaster Recovery）、略してDRと言います。]

ここまでクラウドの良さを色々お話ししてきましたが、もちろんデメリットもあります。

もし何かトラブルがあってフードコート全体がお休みになるときは、問答無用でピザ屋もお休みになってしまいます。つまり使っているクラウドで大規模障害が起きたら、一利用者である私たちにできることはなく復旧までひたすら待つしかない、ということです。AWSでも広範囲にわたる障害はたびたび起きています。たとえば2016年には豪雨による電源障害でサーバに接続できなくなる事象が発生@<fn>{awsTrouble}しました。こうした障害の際もAWSが発表してくれる内容がすべてですので、原因が分かるまで自分で徹底的に調べる、あるいは自力で何とかする、ということはできません。

//footnote[awsTrouble][Amazonクラウドのシドニーリージョン、豪雨による電源障害でEC2などに一部障害。現在は復旧 － Publickey @<href>{https://www.publickey1.jp/blog/16/amazonec2.html}]

またフードコートの通路やトイレ、駐車場といった共有スペースは他店舗（ドーナツ屋やラーメン屋など）と共有していますので、フードコート内で他のお店が混んでくると、駐車場が満車になってピザ屋に来たかったお客さんが入れなかったり、人波が自分の店の方まで押し寄せてきたりとマイナスな影響も受けます。つまり同じクラウド@<fn>{sameCloud}を使っているウェブサイトにアクセスが集中すると、たとえば回線がひっ迫したりして自分のサイトまで繋がりにくくなる、というデメリットがあるということです。

//footnote[sameCloud][他店舗というのは具体的には同じホストサーバを使っている他のゲストサーバ上のサイト。あるいは同じインターネット回線を使っている他のサーバ上のサイトのことです。]

=== AWSはAmazonがやっているクラウド

たくさんお話ししてきたので、一度おさらいをしましょう。

企業が「自社のウェブサイト作りたいなぁ・・・だからサーバが必要だ！」と思ったとき、@<ttb>{自分でサーバを買って自分で管理しなければいけないのがオンプレミス}で、従量課金で@<ttb>{すぐに使えて性能や台数の増減も簡単にできるのがクラウド}です。

そしてようやく最初の話に戻ると、AWSとはAmazon Web Servicesの略で、欲しいものをぽちっとな！すると翌日には届くあの@<ttb>{Amazonがやっているクラウド}なのです。

AWSがなんなのか、お分かりいただけましたでしょうか？

=== パブリッククラウドとプライベートクラウド

ところでパブリッククラウドやプライベートクラウド、という言葉は聞いたことがありますか？AWSのようなクラウドは、@<ttb>{パブリッククラウドと呼ばれる}こともあります。みんなでホストサーバという資源（リソース）を共有して使うので、「公共の」という意味の「パブリック」が付いています。

クラウドが少しずつ使われるようになった頃に「クラウドって便利そうだけど、みんなでサーバを共有するのってちょっと抵抗あるな・・・」と思った人たちを安心させるため、「プライベートクラウド」という言葉が生まれました。このプライベートクラウドとはいったい何なのでしょう？

たとえばオンプレミスの環境で高スペックな物理サーバを買って、ホストサーバにしてその上でゲストサーバ（仮想サーバ）を立てられるようになったとします。これを見て「ホストサーバのスペックが足りる限りという制限はあるものの、好きなときに好きなだけゲストサーバを立てたり増強したりできるのでこれはもはやクラウド！プライベートなクラウドだ！」と言いだした人がいました。また「クラウド事業者が提供しているホストサーバを1台まるまる占有する契約をしたぞ！自社で物理サーバを所有している訳ではないのでこれはクラウドなんだ。しかも他の人はこのホストサーバ上のゲストサーバを使えないから、プライベートなクラウドだ！」と言う人も現れました。定義は曖昧なのですが、このように@<ttb>{みんなで共有せず自社だけで専有できるクラウドをプライベートクラウド}と呼ぶようです。

こうしたプライベートクラウドだと「初期投資額が少ない」「サーバの性能や台数を後から好きなだけ増強できる」といった、@<ttb>{クラウド本来のメリットが享受できない}ように思えます。

そもそもクラウドは英語で書くと「Cloud」（雲）です。物理的な実体や設置してある場所を意識することなく、インターネットという大きな雲の向こう側にあるリソースを好きなように利用できる環境を「クラウド」と呼んでいたはずなのに、果たしてこのようなプライベートクラウドはクラウドなのでしょうか？

このように@<ttb>{クラウドという言葉はとても曖昧}です。結局「クラウド」という言葉の定義がはっきりしていないため、その人が言っている「クラウド」という言葉がなにを指しているのかは、話をよくよく聞いてみないと分からない、ということです。@<fn>{whatIsCloud}

//footnote[whatIsCloud][実際、オンプレミス環境にある仮想サーバをクラウドサーバと呼んでいるケースも多々あります。]

=== AWS以外のクラウド

ところでクラウドはAWS以外にもGoogleのGoogle Cloud Platform@<fn>{gcp}、MicrosoftのAzure（アジュール）@<fn>{azure}、その他にも国内クラウドとしてさくらインターネットがやっているさくらのクラウド@<fn>{sakura}、お名前.comと同じGMOグループのGMOクラウド@<fn>{gmoCloud}などたくさんあります。

//footnote[gcp][@<href>{https://cloud.google.com/}]
//footnote[azure][@<href>{https://azure.microsoft.com/ja-jp/}]
//footnote[sakura][@<href>{https://cloud.sakura.ad.jp/}]
//footnote[gmoCloud][@<href>{https://www.gmocloud.com/}]

その中でもなぜ「AWSがいい」と言われているのでしょうか？

理由は使う人によってそれぞれだと思いますが、私なりの「なぜAWSなのか？」を考えてみました。

2018年時点、クラウド市場ではAWSがシェア33%でトップを独走中@<fn>{cloudShare}です。そのため他のクラウドと比べると、AWSなら使ったことがあり対応可能なエンジニアも多く、何か困ったときに調べて出てくる情報も多い、というのが、私がAWSを選ぶいちばんの理由です。それ以外だと、利益が出た分だけどんどん投資されてサービスが改良されていくため、細かな使い勝手がどんどん良くなっていく@<fn>{improve}、というところもポイントです。

//footnote[cloudShare][2018年第1四半期、クラウドインフラ市場でAWSのシェアは揺るがず33％前後、マイクロソフト、Googleが追撃、IBMは苦戦中。Synergy Research － Publickey @<href>{https://www.publickey1.jp/blog/18/20181aws33googleibmsynergy_research.html}]
//footnote[improve][画面や機能もどんどん変わっていくので、この後出てくる設定画面も、皆さんが手を動かしてやってみる頃には本著のキャプチャとは違うものになっているかも知れません。AWSのいいところでもあり、本やマニュアルを作って説明する側にとってはつらいところでもあります。]

クラウドを選ぶ理由、その中でもAWSを選ぶ理由というのは、普遍的な何かがあるわけではなく、本来は使う人やその上で動かすサービスによって異なるはずです。あなたが動かしたいサービスによっては、AWSではなく他のVPSやオンプレミスの方がいいケースだってもちろんあるはずです。これから使ってみて、あなた自身がAWSの良いところを発見できたらいいですね。
