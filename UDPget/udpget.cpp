#include "udpget.h"
#include "QString"
#include "QFileDialog"
#include "QDateTime"
using namespace std;
#pragma warning(disable:4996)
//头文件
#include"thread1.h"//线程1
#include"thread2.h"//线程2
int iUDP;
udpget::udpget(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui.setupUi(this);
    ui.textEdit->document()->setMaximumBlockCount(6);
    /***本机设定***/
    // Winsows 启用 socket
    WSADATA wsadata;//存放windows socket初始化信息
    if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
    {
        MessageBox(NULL, TEXT("启用 socket 失败"), TEXT("提示"), MB_OK);
        WSACleanup();
        exit(0);
    }
    // 新建 socket
    if ((iUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        MessageBox(NULL, TEXT("新建 socket 失败"), TEXT("提示"), MB_OK);
        WSACleanup();
        exit(0);
    }
    ui.pushButton->setEnabled(false);

}

void udpget::on_PathChoose_clicked(QWidget* parent)
{
    // QDir dir;
    PathName = QFileDialog::getExistingDirectory(this, tr("select str"),
        "./",
        QFileDialog::ShowDirsOnly
        |QFileDialog::DontResolveSymlinks);

    PathName.replace("/", "\\"); //单斜杠转换双斜杠,方便后续存储bin文件
    current_File_time = QDateTime::currentDateTime();
    current_File = current_File_time.toString("yyyy_MM_dd_hh_mm_ss");
    PathName = PathName + "\\" + current_File + ".dat";
    ui.lineEdit_4->setText(PathName);    //文件名称显示
   // dir.mkdir(PathName);    //在目录下创建新文件夹
    ui.pushButton->setEnabled(true);
}
//用来处理网络通信的地址 结构体 描述接受数据或者发送数据的地址等信息的（端口、ip等）
typedef struct sockaddr_in SockAddrIn;
char* temp;
DWORD WINAPI set1(Ui::udpgetClass lpParameter);
void udpget::udpgetc(QWidget* parent) {
    //定义N台电脑的sockaddr_in结构体
    SockAddrIn serverAddr;//服务端
    SockAddrIn* clientAddr = new SockAddrIn[1];//N个客户端

    acIpAddr[0] = new char[20];//ip地址
    bool ok;
    QString IP = ui.lineEdit->text();
    QByteArray ba;
    ba = IP.toLatin1();
    temp = ba.data();
    strncpy(acIpAddr[0], temp, 20);

    QString port = ui.lineEdit_2->text();
    iClientPort[0] = port.toInt(&ok);

    QString type1 = ui.lineEdit_3->text();
    type[0] = type1.toInt(&ok);

    //开始设置
    memset(&clientAddr[0], 0, sizeof(SockAddrIn));
    //客户端电脑的设置
    clientAddr[0].sin_family = AF_INET;
    clientAddr[0].sin_port = htons(iClientPort[0]);
    clientAddr[0].sin_addr.s_addr = inet_addr(acIpAddr[0]);

    /***本机设定***/
    memset(&serverAddr, 0, sizeof(serverAddr));
    // 设置协议 IP 地址及 Port
    //绑定自己的端口
    int iServerPort;
    QString iServerPort1 = ui.lineEdit_5->text();
    iServerPort = iServerPort1.toInt(&ok);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(iServerPort);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // 绑定自己端口，监听端口
    if (::bind(iUDP, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        MessageBox(NULL, TEXT("绑定端口失败"), TEXT("提示"), MB_OK);
        closesocket(iUDP);
        WSACleanup();
        exit(0);
    }

    ui.pushButton->setEnabled(false);
    ui.pushButton_2->setEnabled(false);
    HANDLE Hone1;//线程_主线程
    Hone1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)set1, &ui, 0, NULL);

}



DWORD WINAPI set1(Ui::udpgetClass lpParameter) {
    Ui::udpgetClass ui = lpParameter;
    ui.textEdit_2->append(QString::fromLocal8Bit("UDP连接成功！"));
    HANDLE Hone;//线程1
    Hone = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadOne, &ui, 0, NULL);
    HANDLE Htwo;//线程2
    Htwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadTwo, &ui, 0, NULL);

    //等待线程全部运行完
    WaitForSingleObject(Hone, INFINITE);
    WaitForSingleObject(Htwo, INFINITE);
    return 0;
}

/***结束按钮***/
void udpget::endcode(QWidget* parent) {
    //delete MxArray_M;
    closesocket(iUDP);
    WSACleanup();
    exit(0);
}