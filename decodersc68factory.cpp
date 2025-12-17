#include "decodersc68factory.h"
#include "sc68helper.h"
#include "decoder_sc68.h"
#include "sc68metadatamodel.h"

#include <QMessageBox>

bool DecoderSC68Factory::canDecode(QIODevice *input) const
{
    const QFile * const file = qobject_cast<QFile*>(input);
    if(!file)
    {
        return false;
    }

    SC68Helper helper(file->fileName());
    return helper.initialize();
}

DecoderProperties DecoderSC68Factory::properties() const
{
    DecoderProperties properties;
    properties.name = tr("SC68 Plugin");
    properties.shortName = "sc68";
    properties.filters << "*.sc68" << "*.snd" << "*.sndh";
    properties.description = "Atari ST(E) And Amiga Audio File";
    properties.protocols << "file" << "sc68";
    properties.noInput = true;
    properties.hasAbout = true;
    return properties;
}

Decoder *DecoderSC68Factory::create(const QString &path, QIODevice *input)
{
    Q_UNUSED(input);
    return new DecoderSC68(path);
}

QList<TrackInfo*> DecoderSC68Factory::createPlayList(const QString &path, TrackInfo::Parts parts, QStringList *ignoredPaths)
{
    if(path.contains("://")) //is it one track?
    {
        int track = -1;
        const QString &filePath = SC68Helper::pathFromUrl(path, &track);

        QList<TrackInfo*> playlist = createPlayList(filePath, parts, ignoredPaths);
        if(playlist.isEmpty() || track <= 0 || track > playlist.count())
        {
            qDeleteAll(playlist);
            playlist.clear();
            return playlist;
        }

        TrackInfo *info = playlist.takeAt(track - 1);
        qDeleteAll(playlist);
        playlist.clear();
        return playlist << info;
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
    Q_UNUSED(readOnly);
    return new SC68MetaDataModel(path);
}

#if (QMMP_VERSION_INT < 0x10700) || (0x20000 <= QMMP_VERSION_INT && QMMP_VERSION_INT < 0x20200)
void DecoderSC68Factory::showSettings(QWidget *parent)
{
    Q_UNUSED(parent);
}
#else
QDialog *DecoderSC68Factory::createSettings(QWidget *parent)
{
    Q_UNUSED(parent);
    return nullptr;
}
#endif

void DecoderSC68Factory::showAbout(QWidget *parent)
{
    QMessageBox::about(parent, tr("About SC68 Reader Plugin"),
                       tr("Qmmp SC68 Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>") + "\n" +
                       tr("Based on the source code from the libsc68") + "\n" +
                       tr("Written by Benjamin Gerard (C) 2001"));
}

QString DecoderSC68Factory::translation() const
{
    return QString();
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
#include <QtPlugin>
Q_EXPORT_PLUGIN2(sc68, DecoderSC68Factory)
#endif
