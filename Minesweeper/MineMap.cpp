#include "MineMap.h"
#include <QMessageBox>

MineMap::MineMap(int nRow, int nCol, int nMineNum, QWidget *parent)
    : QWidget(parent)
    , m_nRow(nRow)
    , m_nCol(nCol)
    , m_nMineNum(nMineNum)
    , m_nTimeNum(0)
    , m_nRedFlagNum(nMineNum)
{
    //动态创建二维数组，用于保存块信息
    m_pMapNum = new int *[m_nRow];
    for(int i = 0; i < m_nRow; i++)
    {
        m_pMapNum[i] = new int [m_nCol];
        memset(m_pMapNum[i], 0, m_nCol * sizeof(int));
    }

    // 布雷
    srand((unsigned)time(0));
    for(int i =1; i<= m_nMineNum; i++)
    {
        int num = rand() % (m_nRow * m_nCol) - 1;
        int rowBlock = num / m_nCol;
        int colBlock = num % m_nCol;
        if( m_pMapNum[rowBlock][colBlock] == 99)
        {
            i--;
            continue;
        }

        m_pMapNum[rowBlock][colBlock] = 99;
    }

    //为除炸弹块外赋值，表明周围八位的炸弹数
    for(int i =0;i<m_nRow;i++)
    {
        for(int j = 0;j<m_nCol;j++)
        {
            if(m_pMapNum[i][j]==99)
            {
                continue;
            }

            char blockBoomNum = 0;
            for(int blockRow = i - 1; 0 <= blockRow && blockRow <= i +1; blockRow++)
            {
                for(int blockCol = j -1; 0 <= blockCol && blockCol <= j + 1; blockCol++)
                {
                    //处理特殊情况，比如第一排、第一列等
                    if(blockRow>=m_nRow||blockCol>=m_nCol)
                        continue;

                    //开始检测周围雷数
                    if(99 == m_pMapNum[blockRow][blockCol])
                    {
                        blockBoomNum ++;
                    }
                }
            }

            m_pMapNum[i][j]=blockBoomNum;
        }
    }
    //初始化完成

    this->setFixedSize(getcol() * BLOCK_LENGTH, getrow() * BLOCK_HEIGH + TITILE_HEIGH);

    runtime = new QTimer(this);
    connect(runtime,SIGNAL(timeout()),this,SLOT(on_secondadd()));
    connect(runtime,SIGNAL(timeout()),this,SLOT(update()));
}

MineMap::~MineMap()
{
    for(int i =0;i<m_nRow;i++)
    {
        delete[]  m_pMapNum[i];
    }
    delete [] m_pMapNum;
}
//鼠标事件
void MineMap::mousePressEvent(QMouseEvent *event)
{
    //用户鼠标点击，判断左右键，确定落点，修改块信息，确定是否结束
    click_x = event->x();
    click_y = event->y();

    //先判断是否点击了笑脸
    if(event->buttons()==(Qt::LeftButton)
            &&(click_x>(int)getcol()*BLOCK_LENGTH*100/200-11)&&(click_x<(int)getcol()*BLOCK_LENGTH*100/200+11 +EXPRESSION_LENGHT)
            &&(click_y>7+TTILE_BEGIN) && (click_y<7+TTILE_BEGIN+EXPRESSION_HEIGH))
    {
        qDebug()<<"点击了笑脸";
        return;
    }

    if( click_y < TITILE_HEIGH )
    {
        return;
    }

    if(true == end)
    {
        return;
    }

    //确定落点
    int y = (click_y - TITILE_HEIGH) / BLOCK_HEIGH;
    int x = click_x / BLOCK_LENGTH;
    if(event->buttons() & (Qt::LeftButton))
    {
        runtime->start(1000);
        if(m_pMapNum[y][x] == 99)
        {
            //若点击了炸弹,瞬间爆炸，结束游戏
            paint_flag = 4;
            end = true;
            runtime->stop();
            update();

        }
        else if((m_pMapNum[y][x]<10))
        {
            //需要递归遍历，更改类中信息
            showblock(y,x);
            paint_flag = 2;
            if(true == (end = iswin()))
            {
                paint_flag = 5;
                runtime->stop();
            }
            update();
            if(end)
            {
                if(showimage)
                {
                    QMessageBox message(QMessageBox::NoIcon, "you are win", "very good, I really very appreciate you ");
                    message.setIconPixmap(QPixmap("win.png"));
                    showimage = !showimage;
                    message.exec();
                }
                else
                {
                    QMessageBox message(QMessageBox::NoIcon, "you are win", " I will give you a red flower");
                    message.setIconPixmap(QPixmap("good.png"));
                    showimage = !showimage;
                    message.exec();
                }

            }
        }
        else
        {
            return;
        }
    }
    else if(event->buttons() & (Qt::RightButton))
    {
        //如果点击了右键
        if((m_pMapNum[y][x]<10)||(m_pMapNum[y][x]==99))
        {
            m_pMapNum[y][x] = m_pMapNum[y][x] +50;
            minusredFlagNum();
        }
        else if((m_pMapNum[y][x]>=50&&m_pMapNum[y][x]<60)||(m_pMapNum[y][x]>110))
        {
            m_pMapNum[y][x] = m_pMapNum[y][x] -50;
            addredFlagNum();
        }
        paint_flag = 3;
        if(true == (end = iswin()))
        {
            paint_flag = 5;
            runtime->stop();
        }
        update();
        if(end)
        {
            if(showimage)
            {
                QMessageBox message(QMessageBox::NoIcon, "you are win", "very good, I really very appreciate you ");
                message.setIconPixmap(QPixmap("win.png"));
                showimage = !showimage;
                message.exec();
            }
            else
            {
                QMessageBox message(QMessageBox::NoIcon, "you are win", " I will give you a red flower ");
                message.setIconPixmap(QPixmap("good.png"));
                showimage = !showimage;
                message.exec();
            }
        }
    }
}

//绘图事件
void MineMap::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    //加载位图
    QPixmap block_close(":/res/block_close.bmp");
    QPixmap block_open(":/res/block_open.bmp");
    QPixmap red_flag(":/res/redflag.bmp");
    QPixmap keil_boom(":/res/keilboom.bmp");
    QPixmap click_boom(":/res/clickboom.bmp");
    QPixmap boom(":/res/boom.bmp");

    //绘制标题
    painttitle(&painter);

    //如果是第一次打开，则进行初始化
    if(paint_flag == 0)
    {
        //绘制雷区
        for(int i = 0; i < getcol(); ++i)
        {
            for(int j = 0; j < getrow(); ++j)
            {
                painter.drawPixmap(i * BLOCK_LENGTH, TITILE_HEIGH + j * BLOCK_HEIGH, block_close,0,0,BLOCK_LENGTH,BLOCK_LENGTH);
            }
        }
    }
    //左键点到炸弹绘制
    else if(paint_flag == 4)
    {
        //绘制雷区
        for(int i = 0;i<getrow();i++)
        {
            for(int j = 0;j<getcol();j++ )
            {
                if((m_pMapNum[i][j]<10))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if(99 == m_pMapNum[i][j])
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if (m_pMapNum[i][j]>110)
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((m_pMapNum[i][j]<60)&&(m_pMapNum[i][j]>=50))
                {
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,keil_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
                else if ((m_pMapNum[i][j])>99 && (m_pMapNum[i][j]<110))
                {
                    QString qstrPixmapPath = ":/res/ele" + QString::number((m_pMapNum[i][j] - 100) / 8 + 1) + ".bmp";
                    QPixmap ele_x(qstrPixmapPath);
                    painter.drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
                }
            }
        }
        //绘制点击的炸弹
        painter.drawPixmap(click_x,click_y,click_boom,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
    }
    //左键点到空白绘制
    else if ((2 == paint_flag) || (3 == paint_flag) || (5 == paint_flag))
    {
        //绘制雷区
        paintboom(&painter);
    }
}

//左键遍历递归
void MineMap::showblock(int x,int y)
{
    for(int blockRow = x - 1; blockRow <= x + 1; blockRow++)
    {
        for(int blockCol = y - 1; blockCol <=y + 1; blockCol++)
        {
            if(blockRow<0||blockCol<0||blockRow>=getrow()||blockCol>=getcol())
                continue;
            if(m_pMapNum[blockRow][blockCol]<10)
            {
                m_pMapNum[blockRow][blockCol] =  m_pMapNum[blockRow][blockCol] + 100;
                if(m_pMapNum[blockRow][blockCol]==100)
                    showblock(blockRow,blockCol);
            }
        }
    }
}

//判断是否结束游戏
bool MineMap::iswin()
{
    int cnt = 0;
    for(int row = 0; row <getrow();row++)
        for(int col =0;col<getcol();col++)
        {
            if((m_pMapNum[row][col]>=100)&&(m_pMapNum[row][col]<110))
                cnt++;
        }
    if(cnt>=((getcol()*getrow())-getboomNum()))
        return true;
    else
        return false;
}

//绘制时间红旗数与标题
void MineMap::painttitle(QPainter* painter)
{
    //加载位图
    QPixmap mine_title(":/res/mine_title.bmp");
    QPixmap qq_smile(":/res/smile.bmp");
    QPixmap qq_lose(":/res/lose.bmp");
    QPixmap qq_pround(":/res/proud.bmp");
    QPixmap ele_0(":/res/ele0.bmp");
    QPixmap ele_10(":/res/ele10.bmp");

    //调整大小
    mine_title = mine_title.scaled(QSize(getcol() * BLOCK_LENGTH, 40));

    //显示标题部分
    painter->drawPixmap(0, TTILE_BEGIN, mine_title, 0, 0, 1000, 1000);
    if(paint_flag == 4)
        painter->drawPixmap((int)getcol() * BLOCK_LENGTH*100/200-11,7+TTILE_BEGIN,qq_lose,0,0,1000,1000);
    else if (paint_flag == 5)
        painter->drawPixmap((int)getcol()*BLOCK_LENGTH*100/200-11,7+TTILE_BEGIN,qq_pround,0,0,1000,1000);
    else
        painter->drawPixmap((int)getcol()*BLOCK_LENGTH*100/200-11,7+TTILE_BEGIN,qq_smile,0,0,1000,1000);
    //显示红旗数量
    int redflagnum = getredFlagNum();
    if(redflagnum<0)
    {
        redflagnum = -redflagnum;
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*40)/200-30,5+TTILE_BEGIN,ele_10,0,0,1000,1000);
    }
    else
    {
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*40)/200-30,5+TTILE_BEGIN,ele_0,0,0,1000,1000);
    }

    {
        QString qstrPixmapPath = ":/res/ele" + QString::number(redflagnum/100) + ".bmp";
        QPixmap ele_x(qstrPixmapPath);
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*40)/200-30, 5+TTILE_BEGIN,ele_x,0,0,1000,1000);
    }

    {
        QString qstrPixmapPath = ":/res/ele" + QString::number(redflagnum/10) + ".bmp";
        QPixmap ele_x(qstrPixmapPath);
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*40)/200-30+ELENUM_LENGHT,5+TTILE_BEGIN,ele_x,0,0,MAP_ITEM_WIDTH,MAP_ITEM_HEIGHT);
    }

    {
        QString qstrPixmapPath = ":/res/ele" + QString::number(redflagnum%10) + ".bmp";
        QPixmap ele_x(qstrPixmapPath);
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*40)/200-30+ELENUM_LENGHT+ELENUM_LENGHT,5+TTILE_BEGIN,ele_x,0,0, MAP_ITEM_WIDTH,MAP_ITEM_HEIGHT);
    }

    //显示时间
    int timenum = gettimeNum();
    {
        QString qstrPixmapPath = ":/res/ele" + QString::number(timenum/100) + ".bmp";
        QPixmap ele_x(qstrPixmapPath);
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*163)/200-30, 5 + TTILE_BEGIN, ele_x, 0, 0, MAP_ITEM_WIDTH, MAP_ITEM_HEIGHT);
    }

    {
        QString qstrPixmapPath = ":/res/ele" + QString::number(timenum/10) + ".bmp";
        QPixmap ele_x(qstrPixmapPath);
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*163)/200-30+ELENUM_LENGHT, 5+TTILE_BEGIN, ele_x, 0, 0, MAP_ITEM_WIDTH, MAP_ITEM_HEIGHT);
    }

    {
        QString qstrPixmapPath = ":/res/ele" + QString::number(timenum%10) + ".bmp";
        QPixmap ele_x(qstrPixmapPath);
        painter->drawPixmap((int)(getcol()*BLOCK_LENGTH*163)/200-30+ELENUM_LENGHT+ELENUM_LENGHT, 5+TTILE_BEGIN, ele_x, 0, 0, MAP_ITEM_WIDTH, MAP_ITEM_HEIGHT);
    }
}

// 绘制正常鼠标点击事件与结束的雷区
void MineMap::paintboom(QPainter * painter)
{
    //加载位图
    QPixmap block_close(":/res/block_close.bmp");
    QPixmap block_open(":/res/block_open.bmp");
    QPixmap red_flag(":/res/redflag.bmp");

    for(int i = 0;i<getrow();i++)
    {
        for(int j = 0;j<getcol();j++ )
        {
            if((m_pMapNum[i][j] < 10) || (m_pMapNum[i][j] == 99))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_close,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if(100 == m_pMapNum[i][j])
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,block_open,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if (((m_pMapNum[i][j]<60)&&(m_pMapNum[i][j]>=50))||(m_pMapNum[i][j]>120))
            {
                painter->drawPixmap(j*BLOCK_LENGTH,i*BLOCK_HEIGH+TITILE_HEIGH,red_flag,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
            else if ((m_pMapNum[i][j]>99)&&(m_pMapNum[i][j]<110))
            {
                QString qstrPixmapPath = ":/res/blk" + QString::number(m_pMapNum[i][j] - 100) + ".bmp";
                QPixmap ele_x(qstrPixmapPath);
                painter->drawPixmap(j * BLOCK_LENGTH, i * BLOCK_HEIGH + TITILE_HEIGH, ele_x,0,0,BLOCK_LENGTH,BLOCK_HEIGH);
            }
        }
    }
}

//计时器槽函数
void MineMap::on_secondadd()
{
    addtimeNum();
}


