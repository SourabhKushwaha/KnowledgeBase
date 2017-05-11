#ifndef DATACONVERTER_H
#define DATACONVERTER_H

#include <QObject>

class QByteArray;
class QBitArray;
class QString;
class DataConverter : public QObject {
    Q_OBJECT

public:
    DataConverter(QObject* parent = 0) : QObject(parent) {}
    ~DataConverter() {}

    enum DataType {
        Int = 2,
        LInt = 128,
        UInt = 3,
        Double_16 = 129,
        Double_32 = 130,
        ByteArray = 12,
        BitArray = 13
    };

    Q_ENUMS(DataType)

    static QByteArray checksumBytes(const QByteArray& bytes);
    static double serial16BitDataToDouble(const QByteArray& data);
    static QByteArray doubleToSerial16BitData(double value);
    static double serial32BitDataToDouble(const QByteArray& data);
    static QByteArray doubleToSerial32BitData(double value);
    static double serial64BitDataToDouble(const QByteArray& data);
    static QByteArray doubleToSerial64BitData(double value);
    static int serial16BitDataToInt(const QByteArray& data);
    static QByteArray intToSerial16BitData(int value);
    static unsigned int serial16BitDataToUInt(const QByteArray& data);
    static QByteArray uIntToSerial16BitData(unsigned int value);
    static long int serial32BitDataToLongInt(const QByteArray& data);
    static QByteArray longIntToSerial32BitData(long int value);
    static QBitArray byteArrayToBitArray(const QByteArray& bytes);
    static QByteArray bitArrayToByteArray(const QBitArray& bits, int byteSize);
    static QByteArray commandToDataPacket(int label);
    static QByteArray byteArrayToDataPacket(const QByteArray& data, int preamble = 255);
    static QString boolToString(const bool& val);
    static double toFixed(double number, int precision);
};

#endif // DATACONVERTER_H
