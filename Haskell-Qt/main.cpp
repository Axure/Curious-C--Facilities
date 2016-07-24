#include <iostream>
#include <deque>
#include <sstream>
#include <functional>
#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QTreeView>
#include <QWindow>

class DOM {
 private:
  std::deque<DOM> children_;

 public:
  DOM() {

  }

  virtual ~DOM() {

  }
};

class PropsType {

};

class NoProps : public PropsType {

};

NoProps noProps;

using RenderFunctionType = std::function<std::string(PropsType)>;

class Component {
 public:
  virtual std::string renderToString() = 0;
};

std::string elementFromTag(std::string tag, std::string innerHTML) {
  std::ostringstream ostringstream;
  ostringstream << '<' << tag << '>' << innerHTML << "</" << tag << '>';
  return ostringstream.str();
}

RenderFunctionType elementFunctionFromTag (std::string tag) {
  return [&tag](PropsType props) {
    std::ostringstream ostringstream;
    ostringstream << '<' << tag << '>' << "</" << tag << '>';
    return ostringstream.str();
  };
}

RenderFunctionType elementFunctionFromTag (std::string tag, std::string innerHTML) {
  return [&tag, &innerHTML](PropsType props) {
    std::ostringstream ostringstream;
    ostringstream << '<' << tag << '>' << innerHTML << "</" << tag << '>';
    return ostringstream.str();
  };
}

class FromTag {

};

std::string functionalRendering() {
  std::ostringstream resultStream;

  return resultStream.str();
}


int main(int argc, char** argv) {
  std::cout << "Hello, World!" << std::endl;
  auto div = elementFunctionFromTag("div");
  std::cout << div(noProps);

  QApplication app(argc, argv);
  QWindow mainWindow;

  mainWindow.show();
  return app.exec();
}
