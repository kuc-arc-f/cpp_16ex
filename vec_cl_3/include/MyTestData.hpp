#pragma once
#include <iostream>
#include <vector>
#include <random> // 乱数に必要なヘッダー

class MyTestData {
private:
    std::string m_name;
public:
    explicit MyTestData(std::string str){}
    ~MyTestData() {}

    std::vector<std::string> get_text(){
      std::vector<std::string> vec;
      std::string str1 = R"(Metaは自社のスマートグラスに複数の新しいフレームスタイルを導入する。これらは度付きレンズに対応し、日常生活に溶け込み、一日中装着できるデバイスとしての実用性を高めるものだ。
 また、スマートグラスで見ているものを分析してカロリーを推定したり、「WhatsApp」などのアプリからのメッセージを要約したり、内蔵AIを通じて状況に応じた支援を提供したりする機能も展開する。
 度付きレンズに最適化された新スタイル
 Metaは、「Ray-Ban Meta Optics Styles」として2つの新しいフレームスタイルを導入する。角張った「Blayzer Optics」（標準＆ラージサイズ）と、より軽くスリムなフォルムで丸みを帯びた「Sriber Optics」だ。
 米国など一部の国で4月14日に発売予定で、価格は499ドル（約7万9000円）から。
 「Oakley Meta」シリーズでは、カラーとレンズの組み合わせが大幅に増える。これには、ゴルフ場でより鮮やかな色彩とコントラストを実現する「Prizm Dark Golf」レンズや、屋外の光に合わせて変化する「Prizm Transitions」などが含まれる。「Ray-Ban Meta（Gen 2）」にも季節限定カラーが登場する。
)";
      std::string str2 = R"(Googleは、より多くのAI機能を利用するためにプランのアップグレードを検討しているユーザーに向けて、特典を拡充した。月額2900円の中位プラン「Google AI Pro」では、クラウドストレージを２TBから5TBに拡大。「Gmail」「Googleフォト」「Googleドライブ」などのサービスで利用できる。
【画像】Google AIの3つのプランを見る
「Google Home Premium Standard」プランもバンドルされた。これは単体では月額1000円で、Google Homeデバイスに30日間のイベント履歴などの拡張機能を追加するものだ。
 Google OneおよびGoogle フォト担当のバイスプレジデント兼ゼネラルマネージャーであるShimrit Ben-Yair氏はXへの投稿で、米国ではクラウド容量の追加とともに、Google AI Proや月額3万6400円の「Google AI Ultra」では、オンライン作業を自動化する「Chrome auto browse」などの新機能を利用できるようになると述べた。
 GoogleにはAIに特化した3つのプランがある。AI Pro、AI Ultra、そしてAI Plusだ。最も安価な有料プランであるAI Plusは、月額1200円で200GBのクラウドストレージと、限定的なAI機能へのアクセスを提供する。
)";
      std::string str3 = R"(【画像】AI搭載ワイン冷蔵庫
 サムスンは3月30日、AIを活用して在庫に関するあらゆる重要な情報を提供する家電「Infinite AI Wine Refrigerator」を韓国で発売した。
 この製品は「AI Wine Manager」を採用しており、本体上部に搭載されたカメラ「AI Vision」からの情報に基づいて、長期にわたる細かな管理が必要なワインをより簡単かつ効率的に管理できるという。
 AIカメラはAI Wine Managerアプリと同期し、ボトルの出し入れだけでなく、各ボトルが冷蔵庫内のどこにあるかまで検知する。また、AIが各ボトルのラベルを分析し、ワインの名称や品種、ビンテージ（原料となったブドウの収穫年）を特定できる。ボトルを別の場所に移動させた場合も、AI Wine Managerがその変更を記録する。
 その日の夕食にどのワインを選んでも、それに合う料理のレシピをアプリが提案してくれるとサムスンは説明している。
)";
      std::string str4 = R"(米SpaceXは、衛星インターネットサービス「Starlink」の衛星1機で、軌道上の異常が発生したと明らかにした。対象は衛星「34343」で、日曜日に地上約560km上空で異常が起き、衛星が分解した可能性があるという。
 SpaceXはSNSへの投稿で、今回の事象によって国際宇宙ステーション（ISS）や今後予定されている宇宙ミッションに危険が及ぶことはないと説明した。残骸や追跡可能なデブリについては監視を継続するとしており、「SpaceXとStarlinkのチームは原因の特定を進めており、必要な是正措置を迅速に講じる」としている。
 この件についてSpaceXにコメントを求めたが、記事公開時点で回答は得られていない。
 Starlinkでは、2025年12月にも別の衛星で「異常」とされる事象が発生し、衛星を喪失している。今回のトラブルは、これに続く事案となる。
)";
      std::string str5 = R"(ソフトバンクグループのBBSSは3月31日、ゲーム特化型アプリストア「あっぷアリーナ！」のiOS版の提供を開始した。2025年12月施行のスマホ新法（スマートフォンソフトウェア競争促進法）を受けて参入したサードパーティーストアで、ポルトガルのAptoide社と共同で運営する。Android版は5月1日に提供を開始する。
 App Store以外のストアをiPhoneに入れる
 あっぷアリーナ！のインストールには、通常のApp Storeとは異なる手順が必要になる。ランディングページや広告からインストール用のリンクをタップすると、iOSの設定画面に遷移する。「アプリのインストールを許可しますか」という確認が2段階で表示されるため、それぞれを許可するとストアアプリがダウンロードされる。スマホ新法に基づき、Appleが認めた「代替アプリマーケットプレイス」の仕組みを利用しており、配信されるアプリはすべてAppleの公証（Notarization）審査を通過している。BBSSの橋本雅斗R&D本部長は「Appleの正式な許可を得たサービスだ」と説明した。
 ホーム画面には、緑色の「あ！」をあしらったアイコンが追加される。ストア内では、アプリの紹介、編集部の記事、ポイント残高の確認などがタブごとに整理されている。
)";

      vec.push_back(str1);
      vec.push_back(str2);
      vec.push_back(str3);
      vec.push_back(str4);
      vec.push_back(str5);

      return vec;
    }

    std::string get_items(){
      std::string ret = "";
      std::vector<std::string> target = get_text();
      // 1. 乱数生成器の初期化（std::random_deviceは真の乱数に近いシードを生成）
      std::random_device seed;
      std::mt19937 engine(seed());      
      // 2. 範囲の指定（例：min から max まで、両方含む）
      int min = 0;
      int max = 4;
      std::uniform_int_distribution<int> distribution(min, max);

      // 3. ランダムな値の生成
      int random_value = distribution(engine);
      std::string outStr = target[random_value];

      std::cout << random_value << std::endl;
      //std::cout << "outStr=" << outStr << std::endl;
      ret = outStr;
      return ret;
    }
};
