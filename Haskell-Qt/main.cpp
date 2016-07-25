#include <iostream>
#include <deque>
#include <type_traits>
#include <sstream>
#include <functional>
#include <QWidget>
#include <QApplication>
#include <QFile>
#include <QTreeView>
#include <QMainWindow>
#include <QDebug>

template<class Type>
struct MetaTreeNode {
  using type = Type;
};

template<class ThisType, class ...ChildrenList>
struct MetaTreeNode2 {

};


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

class NoProps: public PropsType {

};

class MainWindowProps: public PropsType {

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

///
/// \param tag The tag of the HTML element created.
/// \return
RenderFunctionType elementFunctionFromTag(std::string tag) {
  return [&tag](PropsType props) {
    std::ostringstream ostringstream;
    ostringstream << '<' << tag << '>' << "</" << tag << '>';
    return ostringstream.str();
  };
}


///
/// \param tag The tag of the HTML element created.
/// \param innerHTML
/// \return
RenderFunctionType elementFunctionFromTag(std::string tag, std::string innerHTML) {
  return [&tag, &innerHTML](PropsType props) {
    std::ostringstream ostringstream;
    ostringstream << '<' << tag << '>' << innerHTML << "</" << tag << '>';
    return ostringstream.str();
  };
}

///
/// This is some of the class
///
class FromTag {

};

std::string functionalRendering() {
  std::ostringstream resultStream;

  return resultStream.str();
}

//createElementFromEnum
//createElementFromClass (meta programming)
//createElementFromString

struct PropTypeBase {

};

class RenderableType {
 public:
  virtual void render() {
    qDebug() << "Start rendering in RenderableType";
    renderSelfPre();
    qDebug() << "Rendering children in RenderableType";
    if (getChildren() != nullptr) {
      for (auto &children: *getChildren()) {
        children.render();
      }
    }
    renderSelfPost();
    qDebug() << "End rendering in RenderableType";
  }
  virtual ~RenderableType() {};
  virtual void renderSelfPre() = 0;
  virtual void renderSelfPost() = 0;
  virtual std::deque<RenderableType> *getChildren() = 0;
  virtual PropsType getProps() = 0;
};

class ReactMainWindow: public RenderableType {
 private:
  QMainWindow *qMainWindow;
  MainWindowProps mainWindowProps_;
 public:
  ReactMainWindow(MainWindowProps &mainWindowProps) : mainWindowProps_(mainWindowProps) {
    qDebug() << "Constructing the main window!";
  }

  virtual void renderSelfPre() {
    qDebug() << "Pre rendering of the main window";
    qMainWindow = new QMainWindow();
  }
  virtual void renderSelfPost() {
    qMainWindow->show();
  }

  virtual ~ReactMainWindow() {
    qDebug() << "Destructing the react main window.";
    if (qMainWindow != nullptr) {
      qDebug() << "Deleting the Qt main window.";
      delete qMainWindow;
    }
  }

  virtual std::deque<RenderableType> *getChildren() {
    return nullptr;
  }
  virtual PropsType getProps() {
    return NoProps();
  };
};

using ComponentType = std::function<RenderableType*(PropsType &)>;

// This should be a meta function.
//std:: RenderableType renderableFromCX(PropsType props) {
//
//}

template<class RenderableType>
RenderableType createElementFromType() {
  static_assert(std::is_base_of<RenderableType, RenderableType>::value,
                "The type must be a subclass of `RenderableType`.");
}

//RenderableType createElementFromClass() {
//  return
//};

// Do the virtual DOM optimizations in `RenderableType`.

void renderComponentWithProps(ComponentType &component, PropsType &props) {
  qDebug() << "Rendering component with props!";
  auto componentInstance = component(props);
  componentInstance->render();
}

int main(int argc, char **argv) {
  std::cout << "Hello, World!" << std::endl;
  auto div = elementFunctionFromTag("div");
  std::cout << div(noProps);

  QApplication app(argc, argv);

  PropsType mainWindowsProps = MainWindowProps();

  ComponentType component = [](PropsType &props) -> RenderableType* {
    qDebug() << "In the component!";
    return new ReactMainWindow((MainWindowProps&)props);
  };

  renderComponentWithProps(component, mainWindowsProps);

  return app.exec();
}
