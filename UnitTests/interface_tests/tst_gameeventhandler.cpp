#include <QtTest>

// add necessary includes here

class gameeventhandler : public QObject
{
    Q_OBJECT

public:
    gameeventhandler();
    ~gameeventhandler();

private slots:
    void test_case1();

};

gameeventhandler::gameeventhandler()
{

}

gameeventhandler::~gameeventhandler()
{

}

void gameeventhandler::test_case1()
{

}

QTEST_APPLESS_MAIN(gameeventhandler)

#include "tst_gameeventhandler.moc"
