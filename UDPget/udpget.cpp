#include "udpget.h"
#include "QString"
#include "QFileDialog"
#include "QDateTime"
using namespace std;
#pragma warning(disable:4996)
//ͷ�ļ�
#include"thread1.h"//�߳�1
#include"thread2.h"//�߳�2
int iUDP;
udpget::udpget(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint);
    ui.setupUi(this);
    ui.textEdit->document()->setMaximumBlockCount(6);
    /***�����趨***/
    // Winsows ���� socket
    WSADATA wsadata;//���windows socket��ʼ����Ϣ
    if (WSAStartup(MAKEWORD(1, 1), &wsadata) == SOCKET_ERROR)
    {
        MessageBox(NULL, TEXT("���� socket ʧ��"), TEXT("��ʾ"), MB_OK);
        WSACleanup();
        exit(0);
    }
    // �½� socket
    if ((iUDP = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        MessageBox(NULL, TEXT("�½� socket ʧ��"), TEXT("��ʾ"), MB_OK);
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

    PathName.replace("/", "\\"); //��б��ת��˫б��,��������洢bin�ļ�
    current_File_time = QDateTime::currentDateTime();
    current_File = current_File_time.toString("yyyy_MM_dd_hh_mm_ss");
    PathName = PathName + "\\" + current_File + ".dat";
    ui.lineEdit_4->setText(PathName);    //�ļ�������ʾ
   // dir.mkdir(PathName);    //��Ŀ¼�´������ļ���
    ui.pushButton->setEnabled(true);
}
//������������ͨ�ŵĵ�ַ �ṹ�� �����������ݻ��߷������ݵĵ�ַ����Ϣ�ģ��˿ڡ�ip�ȣ�
typedef struct sockaddr_in SockAddrIn;
char* temp;
DWORD WINAPI set1(Ui::udpgetClass lpParameter);
void udpget::udpgetc(QWidget* parent) {
    //����N̨���Ե�sockaddr_in�ṹ��
    SockAddrIn serverAddr;//�����
    SockAddrIn* clientAddr = new SockAddrIn[1];//N���ͻ���

    acIpAddr[0] = new char[20];//ip��ַ
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

    //��ʼ����
    memset(&clientAddr[0], 0, sizeof(SockAddrIn));
    //�ͻ��˵��Ե�����
    clientAddr[0].sin_family = AF_INET;
    clientAddr[0].sin_port = htons(iClientPort[0]);
    clientAddr[0].sin_addr.s_addr = inet_addr(acIpAddr[0]);

    /***�����趨***/
    memset(&serverAddr, 0, sizeof(serverAddr));
    // ����Э�� IP ��ַ�� Port
    //���Լ��Ķ˿�
    int iServerPort;
    QString iServerPort1 = ui.lineEdit_5->text();
    iServerPort = iServerPort1.toInt(&ok);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(iServerPort);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // ���Լ��˿ڣ������˿�
    if (::bind(iUDP, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1)
    {
        MessageBox(NULL, TEXT("�󶨶˿�ʧ��"), TEXT("��ʾ"), MB_OK);
        closesocket(iUDP);
        WSACleanup();
        exit(0);
    }

    ui.pushButton->setEnabled(false);
    ui.pushButton_2->setEnabled(false);
    HANDLE Hone1;//�߳�_���߳�
    Hone1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)set1, &ui, 0, NULL);

}



DWORD WINAPI set1(Ui::udpgetClass lpParameter) {
    Ui::udpgetClass ui = lpParameter;
    ui.textEdit_2->append(QString::fromLocal8Bit("UDP���ӳɹ���"));
    HANDLE Hone;//�߳�1
    Hone = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadOne, &ui, 0, NULL);
    HANDLE Htwo;//�߳�2
    Htwo = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadTwo, &ui, 0, NULL);

    //�ȴ��߳�ȫ��������
    WaitForSingleObject(Hone, INFINITE);
    WaitForSingleObject(Htwo, INFINITE);
    return 0;
}

/***������ť***/
void udpget::endcode(QWidget* parent) {
    //delete MxArray_M;
    closesocket(iUDP);
    WSACleanup();
    exit(0);
}