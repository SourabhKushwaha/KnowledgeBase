#include "DataConverter.h"

#include <QByteArray>
#include <QBitArray>
#include <QString>
#include <qmath.h>

QByteArray DataConverter::checksumBytes(const QByteArray& bytes)
{
    uint checksumA = 255;
    uint checksumB = 255;

    for(int i=1; i<bytes.count(); i++){
        checksumA += (unsigned char) bytes.at(i);
        checksumA = checksumA % 256;

        checksumB += checksumA;
        checksumB = checksumB % 256;
    }

    QByteArray checkSumBytes;
    checkSumBytes.append((unsigned char) checksumA);
    checkSumBytes.append((unsigned char) checksumB);
    return checkSumBytes;
}

double DataConverter::serial16BitDataToDouble(const QByteArray& data)
{
    if(data.isEmpty() || (data.size() < 2))
        return 0.0;

    QByteArray tempData;
    tempData.append(data.at(1));
    tempData.append(data.at(0));
    return (tempData.toHex().toInt(0, 16) - 30000) * 0.01;
}

QByteArray DataConverter::doubleToSerial16BitData(double value)
{
    QByteArray data;

    int tempValue = (value * 100) + 30000;
    if(tempValue < 0)
        tempValue = 0;
    else if(tempValue > 65530)
        tempValue = 65530;

    int mostSignificantByte = tempValue / 256;
    int leastSignificantByte = tempValue % 256;

    data.append(leastSignificantByte);
    data.append(mostSignificantByte);
    return data;
}

double DataConverter::serial32BitDataToDouble(const QByteArray& data)
{
    if(data.isEmpty() || (data.size() < 4))
        return 0.0;

    union
    {
        float value;
        struct
        {
            qint8 bytes[4];
        };
    }
    extract_float;

    for(int i=0; i<4; i++)
        extract_float.bytes[i] = (unsigned char) data.at(i);

    return extract_float.value;
}

QByteArray DataConverter::doubleToSerial32BitData(double value)
{
    QByteArray data;

    union
    {
        float value;
        struct
        {
            qint8 bytes[4];
        };
    }
    extract_float;

    extract_float.value = value;

    for(int i=0; i<4; i++)
        data.append((unsigned char) extract_float.bytes[i]);

    return data;
}

double DataConverter::serial64BitDataToDouble(const QByteArray& data)
{
    if(data.isEmpty() || (data.size() < 8))
        return 0.0;

    union
    {
        double value;
        struct
        {
            qint8 bytes[8];
        };
    }
    extract_double;

    for(int i=0; i<8; i++)
        extract_double.bytes[i] = (unsigned char) data.at(i);

    return extract_double.value;
}

QByteArray DataConverter::doubleToSerial64BitData(double value)
{
    QByteArray data;

    union
    {
        double value;
        struct
        {
            qint8 bytes[8];
        };
    }
    extract_double;

    extract_double.value = value;

    for(int i=0; i<8; i++)
        data.append((unsigned char) extract_double.bytes[i]);

    return data;
}

int DataConverter::serial16BitDataToInt(const QByteArray &data)
{
    if(data.isEmpty() || (data.size() < 2))
        return 0.0;

    union
    {
        qint16 value;
        struct
        {
            qint8 bytes[2];
        };
    }
    extract_int;

    for(int i=0; i<2; i++)
        extract_int.bytes[i] = (unsigned char) data.at(i);

    return extract_int.value;
}

QByteArray DataConverter::intToSerial16BitData(int value)
{
    QByteArray data;

    union
    {
        qint16 value;
        struct
        {
            qint8 bytes[2];
        };
    }
    extract_int;

    extract_int.value = value;

    for(int i=0; i<2; i++)
        data.append((unsigned char) extract_int.bytes[i]);

    return data;
}

unsigned int DataConverter::serial16BitDataToUInt(const QByteArray& data)
{
    if(data.isEmpty() || (data.size() < 2))
        return 0.0;

    union
    {
        quint16 value;
        struct
        {
            qint8 bytes[2];
        };
    }
    extract_uint;

    for(int i=0; i<2; i++)
        extract_uint.bytes[i] = (unsigned char) data.at(i);

    return extract_uint.value;
}

QByteArray DataConverter::uIntToSerial16BitData(unsigned int value)
{
    QByteArray data;

    union
    {
        quint16 value;
        struct
        {
            qint8 bytes[2];
        };
    }
    extract_uint;

    extract_uint.value = value;

    for(int i=0; i<2; i++)
        data.append((unsigned char) extract_uint.bytes[i]);

    return data;
}

long int DataConverter::serial32BitDataToLongInt(const QByteArray& data)
{
    if(data.isEmpty() || (data.size() < 4))
        return 0.0;

    union
    {
        qint32 value;
        struct
        {
            qint8 bytes[4];
        };
    }
    extract_int32;


    for(int i=0; i<4; i++)
        extract_int32.bytes[i] = data.at(i);

    return extract_int32.value;
}

QByteArray DataConverter::longIntToSerial32BitData(long int value)
{
    QByteArray data;

    union
    {
        qint32 value;
        struct
        {
            qint8 bytes[4];
        };
    }
    extract_int32;

    extract_int32.value = value;

    for(int i=0; i<4; i++)
        data.append((unsigned char) extract_int32.bytes[i]);

    return data;
}

QBitArray DataConverter::byteArrayToBitArray(const QByteArray& bytes)
{
    QBitArray bits(bytes.count()*8);
    for(int bytePos=0; bytePos<bytes.count(); ++bytePos)
    for(int bitPos=0; bitPos<8; ++bitPos)
        bits.setBit(bitPos, bytes.at(bytePos)&(1<<(7-bitPos)));

    return bits;
}

QByteArray DataConverter::bitArrayToByteArray(
        const QBitArray& bits, int byteSize)
{
    QByteArray bytes;
    if(bits.count()%byteSize)
        return bytes;

    bytes.resize(bits.count()/byteSize);
    bytes.fill(0);

    for(int bitPos=0; bitPos<bits.count(); ++bitPos)
        bytes[bitPos/byteSize] = (bytes.at(bitPos/byteSize) | ((bits[(bits.count()-1) - bitPos]?1:0)<<(bitPos%byteSize)));

    return bytes;
}

QByteArray DataConverter::commandToDataPacket(int label)
{
    QByteArray bytes;
    bytes.append((unsigned char) 255);
    bytes.append((unsigned char) 4);
    bytes.append((unsigned char) label);
    bytes.append(DataConverter::checksumBytes(bytes));
    return bytes;
}

QByteArray DataConverter::byteArrayToDataPacket(const QByteArray& data,
                                                         int preamble)
{
    QByteArray bytes;
    bytes.append((unsigned char) preamble);
    bytes.append((unsigned char) (3+ data.count()));
    bytes.append(data);
    bytes.append(DataConverter::checksumBytes(bytes));
    return bytes;
}

QString DataConverter::boolToString(const bool &val)
{
    return val?"true":"false";
}

double DataConverter::toFixed(double number, int precision)
{
    int multiplicationFactor = 1;
    for(int i=0; i<precision; i++)
        multiplicationFactor *= 10;

    double tempValue = number * multiplicationFactor;
    tempValue = qRound(tempValue);

    return tempValue/multiplicationFactor;
}
