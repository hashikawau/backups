/*
 * _main.cpp
 *
 *  Created on: 2013/08/10
 *      Author: you
 */

#include <iostream>
#include <wx/wxprec.h>
#include <wx/wx.h>

class HelloWorld: public wxFrame {
public:
    HelloWorld(const wxString& title);

    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

private:
DECLARE_EVENT_TABLE()
};

enum {
    Minimal_Quit = wxID_EXIT,
    Minimal_About = wxID_ABOUT
};

BEGIN_EVENT_TABLE(HelloWorld, wxFrame)
EVT_MENU(Minimal_Quit, HelloWorld::OnQuit)
EVT_MENU(Minimal_About, HelloWorld::OnAbout)
END_EVENT_TABLE()

/**
 * wxFrameクラスのコンストラクタ
 */
HelloWorld::HelloWorld(const wxString& title)
        : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(640, 480)) {

// メニューバーの設置
    wxMenu *fileMenu = new wxMenu;

    wxMenu *helpMenu = new wxMenu;
    helpMenu->Append(Minimal_About, wxT("&ヘルプ...\tF1"), wxT("このプログラムについて"));
    fileMenu->Append(Minimal_Quit, wxT("&終了\tAlt-X"), wxT("このプログラムを終了します"));

    wxMenuBar *menuBar = new wxMenuBar();
    menuBar->Append(fileMenu, wxT("&ファイル"));
    menuBar->Append(helpMenu, wxT("&ヘルプ"));

    SetMenuBar(menuBar);

// ステータスバーを設置する
    CreateStatusBar(2);
    SetStatusText(wxT("wxWidgetsにようこそ!"));

    Centre();
}
/**
 * 閉じるを押した際のイベント
 */
void HelloWorld::OnQuit(wxCommandEvent& event) {
    Close(true);
}
/**
 * ヘルプを押した際のイベント
 */
void HelloWorld::OnAbout(wxCommandEvent& event) {

//    wxMessageBox(wxString::Format(wxT("%sにようこそ!\n\n")
//    wxT("これはwxWidgetsの最小アプリです\n")
//    wxT("%s環境で動作しています"), wxVERSION_STRING, wxGetOsDescription()),
//    wxT("このアプリケーションについて"), wxOK | wxICON_INFORMATION, this);
}

class App: public wxApp {
public:
    virtual bool OnInit();
};

IMPLEMENT_APP(App)

bool App::OnInit() {
    HelloWorld* hello = new HelloWorld(wxT("hello"));
    hello->Show(true);

    return true;
}

//int main() {
//
//    std::cout << "aaaa" << std::endl;
//
//    return 0;
//}

