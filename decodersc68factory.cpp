#include "decodersc68factory.h"
#include "sc68helper.h"
#include "decoder_sc68.h"

#include <QMessageBox>

bool DecoderSC68Factory::canDecode(QIODevice *input) const
{
    QFile *file = static_cast<QFile*>(input);
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
        QString filePath = path;
        filePath.remove("sc68://");
        filePath.remove(QRegExp("#\\d+$"));

        const int track = path.section("#", -1).toInt();
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
    else
    {
        if(ignoredPaths)
        {
            ignoredPaths->push_back(path);
        }
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
    QMessageBox::about(parent, tr("About SC68 Reader Plugin"),
                       tr("Qmmp SC68 Reader Plugin") + "\n" +
                       tr("Written by: Greedysky <greedysky@163.com>"));
}

QString DecoderSC68Factory::translation() const
{
    return QString();
}
