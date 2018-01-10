#ifndef ABIFSEQUENCETRACE_H
#define ABIFSEQUENCETRACE_H
#include "abstracttracereader.h"


class AbifDir;
class AbifTraceReader;

// define directory from specification
// Check specification from http://www6.appliedbiosystems.com/support/software_community/ABIF_File_Format.pdf

class AbifDir{
public:
    QString name;
    qint32 number = 0 ;
    qint16 elementType = 0;
    qint16 elementsize = 0;
    qint32 numElements = 0;
    qint32 dataSize = 0;
    qint32 dataOffset = 0;
    qint32 dataHandle = 0;
    qint32 offset = 0;

};

class AbifTraceReader : public AbstractTraceReader
{
public:
    enum Type {
        Byte    = 1,
        Char    = 2,
        Word    = 3,
        Short   = 4,
        Long    = 5,
        Float   = 7,
        Double  = 8,
        Date    = 10,
        Time    = 11,
        PString = 18,
        CString = 19,
        Thumb   = 12,
        Bool    = 13,
        User    = 1024
    };
    AbifTraceReader(QIODevice * device);

    const QHash<QChar, QVector<int>>& readDatas() const override;
    const Sequence& readSequence()const  override;
    const QVector<int>& readBaseLocations()const  override;
    const QVector<int>& readBaseScores()const  override;
    const QHash<QString, QVariant>& readMetadatas() const override;



    int version() const;
    QStringList keys() const;
    QVariant data(const QString& key);

protected:
    /*!
     * \brief loadData
     * Read abif device data
     * \return
     */
    bool loadData();
    /*!
     * \brief readDictionnaries
     * read all AbifDir from the device
     */
    void readDictionnaries();
    /*!
     * \brief Read trace from device
     */
    void readTraces();

    /*!
     * \brief readBaseCalls
     * Read basecalls from device
     */
    void readBaseCalls();

    /*!
     * \brief readBaseLocations
     * read base location from device
     */
    void readBaseLocations();

    /*!
     * \brief readConfScores
     * read confident score from device
     */
    void readConfScores();


    /*!
     * \brief dirFromOffset
     * \param offset
     * Read AbifDir (28 bytes) from a specific offset.
     * \return AbifDir
     */
    AbifDir dirFromOffset(int offset);
    /*!
     * \brief fromDir
     * \param dir
     * Read data from a specific AbifDir
     * \return QVariant
     */
    QVariant fromDir(const AbifDir& dir);
    /*!
     * \brief reduce
     * helper function. Convert a one element QVariantList to QVariant
     * \param QVariantList
     * \return QVariant
     */
    QVariant reduce(QVariantList& list);

private:
    qint16 mVersion;
    QMap<QString,AbifDir> mDirs;  // keys = name.number
    AbifDir mRootDir; // root dir

    // store data
    QHash<QChar, QVector<int>> mTraces;
    QHash<QString, QVariant> mMetadatas;
    QVector<int> mBaseLocations;
    QVector<int> mConfScores;
    Sequence mBaseCalls;
//    QIODevice * mDevice;


};



#endif // ABIFSEQUENCETRACE_H