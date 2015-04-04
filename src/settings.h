#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include <glibmm.h>
#include <libconfig.h++>
using libconfig::Setting;

#include <map>

#include "booru/site.h"
#include "imagebox.h"

namespace AhoViewer
{
    class SettingsManager
    {
    public:
        SettingsManager();
        ~SettingsManager();

        bool get_bool(const std::string &key) const;
        int get_int(const std::string &key) const;

        std::vector<std::shared_ptr<Booru::Site>> get_sites();

        std::string get_keybinding(const std::string &group, const std::string &name) const;
        void set_keybinding(const std::string &group, const std::string &name, const std::string &value);

        bool get_geometry(int &x, int &y, int &w, int &h) const;
        void set_geometry(const int x, const int y, const int w, const int h);

        bool get_last_open_file(std::string &path) const;

        Gdk::Color get_background_color() const;
        void set_background_color(const Gdk::Color &value);

        Booru::Site::Rating get_booru_max_rating() const;
        void set_booru_max_rating(const Booru::Site::Rating value);

        ImageBox::ZoomMode get_zoom_mode() const;
        void set_zoom_mode(const ImageBox::ZoomMode value);

        const std::string get_booru_path() const { return BooruPath; }

        void remove(const std::string &key);

        void set(const std::string &key, const bool value)
        {
            set(key, value, Setting::TypeBoolean);
        }
        void set(const std::string &key, const int value)
        {
            set(key, value, Setting::TypeInt);
        }
        void set(const std::string &key, const std::string &value)
        {
            set(key, value, Setting::TypeString);
        }
    private:
        libconfig::Config Config;

        const std::string Path;
        const std::string BooruPath;

        const std::map<std::string, bool> DefaultBools;
        const std::map<std::string, int> DefaultInts;
        const std::vector<std::shared_ptr<Booru::Site>> DefaultSites;
        const std::map<std::string, std::map<std::string, std::string>> DefaultKeybindings;
        const Gdk::Color DefaultBGColor;
        const Booru::Site::Rating DefaultBooruMaxRating = Booru::Site::Rating::EXPLICIT;
        const ImageBox::ZoomMode DefaultZoomMode = ImageBox::ZoomMode::MANUAL;

        std::vector<std::shared_ptr<Booru::Site>> m_Sites;

        template<typename T>
        void set(const std::string &key, const T value, Setting::Type type)
        {
            set(key, value, type, Config.getRoot());
        }
        template<typename T>
        void set(const std::string &key, const T value, Setting::Type type, Setting &s)
        {
            if (!s.exists(key))
                s.add(key, type);

            s[key] = value;
        }
    };

    extern SettingsManager Settings;
}

#endif /* _SETTINGS_H_ */
