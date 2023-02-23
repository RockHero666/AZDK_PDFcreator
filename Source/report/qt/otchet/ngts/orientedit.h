#ifndef ORIENTEDIT_H
#define ORIENTEDIT_H

#include <QtWidgets/QWidget>
#include <QtCore/QStringList>
#include <QtWidgets/QDoubleSpinBox>

class quaternion;
class QSettings;
class vector3d;

class OrientEdit : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(QString var1name READ varName1 WRITE setVarName1)
    Q_PROPERTY(QString var2name READ varName2 WRITE setVarName2)
    Q_PROPERTY(QString var3name READ varName3 WRITE setVarName3)

    Q_PROPERTY(double var1min READ varMin1 WRITE setVarMin1)
    Q_PROPERTY(double var2min READ varMin2 WRITE setVarMin2)
    Q_PROPERTY(double var3min READ varMin3 WRITE setVarMin3)

    Q_PROPERTY(double var1max READ varMax1 WRITE setVarMax1)
    Q_PROPERTY(double var2max READ varMax2 WRITE setVarMax2)
    Q_PROPERTY(double var3max READ varMax3 WRITE setVarMax3)

    Q_PROPERTY(double var1step READ varStep1 WRITE setVarStep1)
    Q_PROPERTY(double var2step READ varStep2 WRITE setVarStep2)
    Q_PROPERTY(double var3step READ varStep3 WRITE setVarStep3)

    Q_PROPERTY(int var1decimals READ varDecimals1 WRITE setVarDecimals1)
    Q_PROPERTY(int var2decimals READ varDecimals2 WRITE setVarDecimals2)
    Q_PROPERTY(int var3decimals READ varDecimals3 WRITE setVarDecimals3)
    Q_PROPERTY(int type READ type WRITE setType)
    Q_PROPERTY(bool orientAngles READ orientAngles WRITE setOrientAngles)

public:
    enum OE_TYPE {
        OE_NONE,
        OE_QUAT,
        OE_VECTOR
    };
    Q_ENUM(OE_TYPE)

    OrientEdit(QWidget *parent = 0);
    ~OrientEdit();
    double value(int w) const;
    void setValue(int w, double v);
    void setRange(int w, double min, double max, double step = -1.0);
    void fromSettings(QSettings &s);
    void toSettings(QSettings &s);

    quaternion getQuaternion() const;
    vector3d getVector() const;
    void setQuaternion(const quaternion &q);
    void setVector(const vector3d & v);

    void setDecimals(int n, int k = -1);

    void setStep(double st, int k = -1);

    void setType(int v) { mType = v; }
    int type() const { return mType; }

    bool orientAngles() const { return mOrieinAngles; }
    void setOrientAngles(bool on) { mOrieinAngles = on; }

public:
    template<int w>
    void setVarName(const QString &name)
    {
        mVarNames[w] = name;
        mAngles[w]->setPrefix(name + ": ");
    }

    void setAngles(double ra, double de, double phi);

protected:
    void copyValue(QDoubleSpinBox* w) const;
    void pasteValue(QDoubleSpinBox* w);
    void customContextMenuEvent(const QPoint& p);

signals:
    void quatChanged(const quaternion &);
    void quatEdited(const quaternion &);
    void vectorChanged(const vector3d &);
    void vectorEdited(const vector3d &);
    void valueChanged();

private:
    QDoubleSpinBox * mAngles[3];
    QStringList mVarNames;
    double mOldVals[3];

    const QString & varName1() const { return mVarNames.at(0); }
    const QString & varName2() const { return mVarNames.at(1); }
    const QString & varName3() const { return mVarNames.at(2); }
    void setVarName1(const QString & v) { setVarName<0>(v); }
    void setVarName2(const QString & v) { setVarName<1>(v); }
    void setVarName3(const QString & v) { setVarName<2>(v); }

    double varStep1() const { return mAngles[0]->singleStep(); }
    double varStep2() const { return mAngles[1]->singleStep(); }
    double varStep3() const { return mAngles[2]->singleStep(); }
    void setVarStep1(double v) { mAngles[0]->setSingleStep(v); }
    void setVarStep2(double v) { mAngles[1]->setSingleStep(v); }
    void setVarStep3(double v) { mAngles[2]->setSingleStep(v); }

    double varMin1() const { return mAngles[0]->minimum(); }
    double varMin2() const { return mAngles[1]->minimum(); }
    double varMin3() const { return mAngles[2]->minimum(); }
    void setVarMin1(double min) { mAngles[0]->setMinimum(min); }
    void setVarMin2(double min) { mAngles[1]->setMinimum(min); }
    void setVarMin3(double min) { mAngles[2]->setMinimum(min); }

    double varMax1() const { return mAngles[0]->maximum(); }
    double varMax2() const { return mAngles[1]->maximum(); }
    double varMax3() const { return mAngles[2]->maximum(); }
    void setVarMax1(double max) { mAngles[0]->setMaximum(max); }
    void setVarMax2(double max) { mAngles[1]->setMaximum(max); }
    void setVarMax3(double max) { mAngles[2]->setMaximum(max); }

    int varDecimals1() const { return mAngles[0]->decimals(); }
    int varDecimals2() const { return mAngles[1]->decimals(); }
    int varDecimals3() const { return mAngles[2]->decimals(); }
    void setVarDecimals1(int d) { mAngles[0]->setDecimals(d); }
    void setVarDecimals2(int d) { mAngles[1]->setDecimals(d); }
    void setVarDecimals3(int d) { mAngles[2]->setDecimals(d); }

    void blockAllSignals(bool on);

    bool isValueChanged(bool update = true);

    int mType = OE_NONE;

    bool mOrieinAngles = true;
};

#endif // ORIENTEDIT_H
