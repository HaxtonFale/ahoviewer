#include "archive.h"
using namespace AhoViewer;

Archive::Image::Image(const std::string &path, const Archive &archive)
  : AhoViewer::Image(Glib::build_filename(archive.get_extracted_path(), path)),
    m_ArchiveFilePath(path),
    m_Archive(archive)
{
    m_Loading = true;
}

std::string Archive::Image::get_filename() const
{
    return Glib::build_filename(Glib::path_get_basename(m_Archive.get_path()),
                                Glib::path_get_basename(m_Path));
}

const Glib::RefPtr<Gdk::Pixbuf>& Archive::Image::get_thumbnail()
{
    if (!m_ThumbnailPixbuf)
    {
        extract_file();
        create_thumbnail();
    }

    return m_ThumbnailPixbuf;
}

void Archive::Image::load_pixbuf()
{
    if (!m_Pixbuf)
    {
        extract_file();
        if (!m_isWebM)
        {
            Glib::RefPtr<Gdk::PixbufAnimation> p = Gdk::PixbufAnimation::create_from_file(m_Path);
            Glib::Threads::Mutex::Lock lock(m_Mutex);
            m_Pixbuf = p;
        }
        m_Loading = false;
        m_SignalPixbufChanged();
    }
}

void Archive::Image::extract_file()
{
    // This lock is needed to prevent the cache thread and
    // the thumbnail thread from stepping on each other's toes
    Glib::Threads::Mutex::Lock lock(m_Mutex);
    if (!Glib::file_test(m_Path, Glib::FILE_TEST_EXISTS))
        m_Archive.extract(m_ArchiveFilePath);
}
