#include <iostream>
#include <Wt/WApplication.h>
#include <Wt/WText.h>
#include <Wt/WImage.h>
#include <Wt/WStackedWidget.h>
#include <Wt/WMenu.h>
#include <Wt/WNavigationBar.h>
#include <filesystem>
#include <random>

auto get_random_file(const std::filesystem::path &path){
    auto count = std::count_if(std::filesystem::directory_iterator(path),
        std::filesystem::directory_iterator(),
        [](auto file){
            return std::filesystem::is_regular_file(file);
        }
    );
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, count-1);
    std::mt19937 gen(rd());
    auto file_num = dist(gen);
    auto file_it = std::filesystem::directory_iterator(path);
    for(size_t i=0; i<file_num; i++){
        file_it++;
    }
    auto file_path = (*file_it).path();
    return file_path;
}

class site_header:public Wt::WNavigationBar{
    Wt::WMenu *menu;
    std::unique_ptr<Wt::WStackedWidget> content_stack;
public:
    site_header():
        Wt::WNavigationBar()
    {
        setStyleClass("navbar");
        content_stack = std::make_unique<Wt::WStackedWidget>();
        auto left_menu = addMenu(std::make_unique<Wt::WMenu>(content_stack.get()));
        left_menu->setStyleClass("navbar-list");
        const size_t size = 5;
        Wt::WMenuItem ** items = new Wt::WMenuItem*[size];
        for(size_t i=0; i<size; i++){
            auto txt = "label"+std::to_string(i);
            items[i] = left_menu->addItem(txt, std::make_unique<Wt::WText>(txt));
            items[i]->setStyleClass("navbar-item");
        }
        items[0]->setLink(Wt::WLink(Wt::LinkType::InternalPath, "/"));
        items[0]->setText("~");
        items[1]->setText("Interesting stuff");
        items[1]->setLink(Wt::WLink(Wt::LinkType::Url, "https://youtu.be/qn9FkoqYgI4"));
    }
};

class hello_wt:public Wt::WApplication{
    site_header *header;
public:
    hello_wt(const Wt::WEnvironment &env)
        :Wt::WApplication(env)
    {
        useStyleSheet("styles/style.css");
        setTitle("project_hello");
        this->header = root()->addNew<site_header>();
        root()->setStyleClass("dark-theme");
        root()->setMargin(0);
        root()->setPadding(0);
        auto path = std::filesystem::current_path();
        path += "/resources";
        auto file_path = get_random_file(path);
        auto wt_path = std::string("resources/")+file_path.filename().string();
        auto gif = root()->addNew<Wt::WImage>(Wt::WLink(wt_path));
        gif->addStyleClass("home-media");
        this->header->addStyleClass("header");
    }
};

int main(int argc, char** argv) {
    return Wt::WRun(argc, argv, [](const auto &env){
            return std::make_unique<hello_wt>(env);
        });
    std::cout << "Hello, world!\n";
}
