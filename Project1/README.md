# プロジェクト1 (Visual Studio C++ プロジェクト)

このプログラムは簡単なシューティングゲームです。
プレイヤーはキャラクターを選択し、敵を倒すことを目的としています。
ゲーム内では弾の種類やカードシステムがあり、同じカードを複数回とることで、
プレイヤーのステータスが強化されます。

カードのイラストは `assets/images/` に配置されており、ゲーム実行時に参照されます。
ステータス強化のカードイラストは作成しましたが、そのほかのカードイラストは未作成なので、必要に応じて追加してください。


トップレベルファイル:
- `Project1.sln`  (Visual Studio ソリューション)
- `Project1.vcxproj`  (Visual Studio プロジェクト)

## SDL2 導入手順（Windows11 / Visual Studio 2022 Community）

### 0. 前提条件 gitと Visual Studio 2022 Community のインストールをお願いします

##  SDL2 関連ライブラリを用意
Microsoft vcpkg を使用してSDL2を導入する方法を推奨します。以下の手順で進めてください。

Microsoft vcpkg のインストール手順は以下の通りです。
### 1. Microsoft vcpkg の GitHub リポジトリにアクセスし、リポジトリをクローンします。
https://github.com/microsoft/vcpkg　このリンクがMicrosoft vcpkg の GitHub リポジトリです。


### 2. 次に、新しいフォルダをローカルフォルダの任意の場所に作成し、ターミナルを開いて、先ほど作成したフォルダに移動します。
例: C:\dev\VCPKG

### 3.ターミナルで以下のコマンドを実行する。
git clone https://github.com/microsoft/vcpkg.git


### 4. vcpkgのセットアップ
クローンが完了したら、vcpkgフォルダに移動し、以下のコマンドを実行します。
.\bootstrap-vcpkg.bat

	
### 5. 環境変数の設定
環境変数の設定を行います。vcpkgフォルダのパスをコピーし、環境変数の「システム環境変数 または ユーザー環境変数 -> Path ->編集」に移動します。
右上にある「新規」をクリックし、コピーしたパスを貼り付けて「OK」をクリックします。


### 6. SDL2 のインストール
sdl2をインストールする作業に移ります。
任意のフォルダに移動し、ターミナルで以下のコマンドを実行します。
	vcpkg search sdl2 
この後に、インストール可能なsdl2のパッケージが表示されますので、以下のコマンドを実行してインストールします。
	vcpkg integrate install 
	vcpkg install sdl2 sdl2-image sdl2-ttf
インストールに成功したら、Visual Studio でプロジェクトを開き、このプログラムをビルドして実行することができます。
### 7. 6 のコマンド解説
vcpkg integrate install コマンドを実行することで、Visual Studio が自動的に vcpkg のライブラリを認識するようになります。
vcpkg install sdl2 sdl2-image sdl2-ttf コマンドを実行することで、SDL2、SDL2_image、SDL2_ttf のライブラリがインストールされます。
## フォルダ構成

```
├── Project1.sln
├── Project1/
│   ├── Project1.vcxproj
│   ├── README.md
│   ├── assets/
│   │   ├── fonts/
│   │   ├── images/
│   │   └── sounds/
│   ├── src/
│   │   ├── Main.cpp
│   │   ├── bar/
│   │   │   └── bars/
│   │   ├── bullet/
│   │   │   └── bullets/
│   │   │       ├── bulletsType/
│   │   │       ├── enemyBullets/
│   │   │       └── playerBullets/
│   │   ├── card/
│   │   │   └── cards/
│   │   ├── common/
│   │   │   └── calcDamage/
│   │   ├── enemy/
│   │   │   └── enemies/
│   │   ├── lib/
│   │   ├── loader/
│   │   │   ├── data/
│   │   │   └── loaders/
│   │   ├── player/
│   │   │   └── players/
│   │   └── windows/
│   │       ├── characterSelect/
│   │       ├── finish/
│   │       ├── game/
│   │       └── menu/
│   └── x64/
└── x64/
```

---

## 実行後の遊び方

1. ゲームを起動したら、メニュー画面から開始します。
2. キャラクター選択画面で使用キャラクターを選びます。
3. ゲーム画面で敵を倒しながら生存します。
4. カード獲得時に強化内容を選びます。
5. 同じ系統のカードを重ねることで、ステータスをさらに強化できます。
6. 被弾を避けつつ、より長く戦って敵全滅を目指してください。

※ カード画像は `assets/images/` を参照します。必要に応じて画像を追加してください。
