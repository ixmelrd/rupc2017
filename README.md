# RUPC 2017 (仮)

## これ何？

阪大と立命の有志(OB含む)によるプログラミングコンテストの準備プロジェクトです．
gitとRimeを利用しているので，下記の方法に従ってインストールしてください．
コードの実行にgcc (Java使いがいればJavaも) も必要です．

ジャッジ解は問題ディレクトリの下にある個人の名前のディレクトリの中にあります．ジェネレータ・バリデータ等は tests ディレクトリ以下にあります．

## gitのインストール

aptやyumで普通にインストールできます．
```
$ sudo apt-get install git
```

## Rimeのインストール

Ubuntu 16.04で確認．Macでもおそらく同じ．Windowsはmsys2で動作確認．

まずPython2が入っているか確認する
```
$ python -V
Python 2.7.13
```
コマンドが無いまたはバージョンが2.\*.\*でない場合はpyenvなどを使ってインストール．
aptなどでもいいが，下記(2)(3)の方法を使う場合にrimeのシェバンは `#!/usr/bin/python` であることに注意．
```
$ cd rupc2017
$ pyenv install 2.7.13
$ pyenv rehash
$ pyenv local 2.7.13
```

Rimeをインストールする．ここでは公式ではなくJAGによる拡張版を使う(公式でも良い)．3つの方法があるので好きな方法を使う．

(1) pipを使う方法(標準的)
```
$ pip install git+https://github.com/icpc-jag/rime-plus
```

(2) 手っ取り早い方法 (パスが通った場所に置く)
```
sudo git clone https://github.com/icpc-jag/rime-plus.git /usr/local/share/rime-plus
sudo ln -s /usr/local/share/rime-plus/rime.py /usr/local/bin/rime
```

(3) もっと手っ取り早い方法　(`~/rime/`などの適当な場所に置いて毎回直接実行する)
```
git clone https://github.com/icpc-jag/rime-plus.git ~/rime
```
この方法を取った場合，以降のrimeコマンドは`~/rime/rime.py`あるいは`python2 ~/rime/rime.py`になって面倒なのでおすすめしない．

インストールが上手くいっているか確認する
```
$ rime
rime.py <command> [<options>...] [<args>...]

Rime is a tool for programming contest organizers to automate usual, boring
and error-prone process of problem set preparation. It supports various
programming contest styles like ACM-ICPC, TopCoder, etc. by plugins.

To see a brief description and available options of a command, try:

rime.py help <command>
(略)
```


テストが走ることを確認する
```
$ rime test
[ COMPILE  ] A+B/tests: generator.cc
[ COMPILE  ] A+B/tests: validator.cc
[ GENERATE ] A+B/tests: generator.cc
(略)
```

## リンク

- [作問ツールの使い方](https://drive.google.com/file/d/0B8nawKhBgu7IV0hTcnNMUEhqb2c/view?usp=sharing)
- [Google Drive](https://drive.google.com/drive/folders/0B8nawKhBgu7IZ2xXeHY1bWJ4MDg)
- [Rime 1.0 documentation](https://rime.readthedocs.io/ja/latest/)
- [testlib](http://codeforces.com/testlib)
- [競技プログラミングの作問進行法](http://itohjam.hatenablog.com/entry/2014/12/02/214019)
