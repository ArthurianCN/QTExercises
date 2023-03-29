#include "MineMap.h"

#include <QGridLayout>


MineMap::MineMap(int nCol, int nRow, int nBoomNum, QWidget *parent)
    : QWidget(parent)
    , m_nCol(nCol)
    , m_nRow(nRow)
    , m_nBoomNum(nBoomNum)
{
    m_pMapInfo = new MineItem *[m_nRow];
    for(int i = 0; i < m_nRow; i++)
    {
        m_pMapInfo[i] = new MineItem[m_nCol];
    }


    //布雷：产生随机数炸弹，将对应块赋值为99
    srand((unsigned)time(0));
    for(int i =1;i <= m_nBoomNum; i++)
    {
         int num = rand() % (m_nRow * m_nCol)-1;
         int rowBlock = num / m_nCol;
         int colBlock = num % m_nCol;
         if( m_pMapInfo[rowBlock][colBlock].GetBoomNum() == 99)
         {
             i--;
             continue;
         }
         else
         {
             m_pMapInfo[rowBlock][colBlock].setBoomNum(99);
         }
    }

    //为除炸弹块外赋值，表明周围八位的炸弹数
    for(int i =0;i< m_nRow; i++)
    {
        for(int j = 0; j < m_nCol; j++)
        {
            if(m_pMapInfo[i][j].GetBoomNum() == 99)
            {
                continue;
            }

            // 遍历九宫格里面的雷数
            int blockBoomNum = 0;
            for(int blockRow = i - 1; blockRow <= i +1 ;blockRow++)
            {
                if((blockRow >= m_nRow) || ( 0 > blockRow))
                {
                    continue;
                }

                for(int blockCol = j -1;(blockCol<=j + 1); blockCol++)
                {
                    if((0 > blockCol) || (blockCol >= m_nCol))
                    {
                        continue;
                    }

                    //开始检测周围雷数
                    if(m_pMapInfo[blockRow][blockCol].GetBoomNum() == 99)
                    {
                        blockBoomNum ++;
                    }
                }
            }

            m_pMapInfo[i][j].setBoomNum(blockBoomNum);
        }
    }

    QGridLayout* layout = new QGridLayout(this);

    for (int i = 0; i < m_nCol * m_nRow; ++i)
    {
        MineItem* pItem = &m_pMapInfo[i / m_nCol][i % m_nCol];
        pItem->setText(QString::number(m_pMapInfo[i / m_nCol][i % m_nCol].GetBoomNum()));
        pItem->setParent(this);
        pItem->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
        layout->addWidget(pItem, i / m_nCol, i % m_nCol);
        connect(pItem, &MineItem::clicked, [=](){
            qDebug("点击的数字为：%d", pItem->GetBoomNum());

        });
    }
}

MineMap::~MineMap()
{

}
