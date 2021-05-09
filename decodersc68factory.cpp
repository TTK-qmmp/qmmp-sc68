#include "sc68helper.h"
#include "decoder_sc68.h"
#include "decodersc68factory.h"

#include <QMessageBox>

bool DecoderSC68Factory::canDecode(QIODevice *) const
{
    return false;
}

DecoderProperties DecoderSC68Factory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("SC68 Plugin");
    properties.filters << "*.sc68";
    properties.description = tr("Atari ST(E) And Amiga Audio Files");
    properties.shortName = "sc68";
    properties.noInput = true;
    properties.protocols << "sc68";
    return properties;
}

Decoder *DecoderSC68Factory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderSC68(path);
}

QList<TrackInfo*> DecoderSC68Factory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *ignoredFiles)
{
    if(path.contains("://")) //is it one track?
    {
        QString filePath = path;
        filePath.remove("sc68://");
        filePath.remove(QRegExp("#\\d+$"));

        const int track = path.section("#", -1).toInt();
        QList<TrackInfo*> list = createPlayList(filePath, parts, ignoredFiles);
        if(list.isEmpty() || track <= 0 || track > list.count())
        {
            qDeleteAll(list);
            list.clear();
            return list;
        }

        TrackInfo *info = list.takeAt(track - 1);
        qDeleteAll(list);
        return QList<TrackInfo*>() << info;
    }
    else
    {
        if(ignoredFiles)
            ignoredFiles->push_back(path);
    }

    SC68Helper helper(path);
    if(!helper.initialize())
    {
        qWarning("DecoderSC68Factory: unable to open file");
        return QList<TrackInfo*>();
    }
    return helper.createPlayList(parts);
}

MetaDataModel* DecoderSC68Factory::createMetaDataModel(const QString &path, bool readOnly)
{
    Q_UNUSED(path);
    Q_UNUSED(readOnly);
    return nullptr;
}

void DecoderSC68Factory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}

void DecoderSC68Factory::showAbout(QWidget *parent)
{
    QMessageBox::about (parent, tr("About SC68 Reader Plugin"),
                        tr("Qmmp SC68 Reader Plugin")+"\n"+
                        tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderSC68Factory::translation() const
{
    return QString();
}
