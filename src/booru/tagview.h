#ifndef _TAGVIEW_H_
#define _TAGVIEW_H_

#include "tagentry.h"

namespace AhoViewer
{
    namespace Booru
    {
        class TagView : public Gtk::TreeView
        {
        public:
            typedef sigc::signal<void, const std::string> SignalNewTabTag;

            TagView(BaseObjectType *cobj, const Glib::RefPtr<Gtk::Builder> &bldr);
            ~TagView() = default;

            void clear() { m_ListStore->clear(); }

            void show_favorite_tags() { set_tags(*m_FavoriteTags); }
            void set_tags(const std::set<std::string> &tags);

            SignalNewTabTag signal_new_tab_tag() const { return m_SignalNewTabTag; }
        protected:
            virtual void on_style_changed(const Glib::RefPtr<Gtk::Style>&);
            virtual bool on_button_press_event(GdkEventButton *e);
        private:
            struct ModelColumns : public Gtk::TreeModelColumnRecord
            {
                ModelColumns() { add(tag); }
                Gtk::TreeModelColumn<std::string> tag;
            };

            void on_favorite_cell_data(Gtk::CellRenderer *c, const Gtk::TreeIter &iter);

            void on_toggle_cell_data(Gtk::CellRenderer *c, const Gtk::TreeIter &iter);
            void update_favorite_icons();

            static const std::string StarSVG,
                                     StarOutlineSVG;

            ModelColumns m_Columns;
            Glib::RefPtr<Gtk::ListStore> m_ListStore;

            TagEntry *m_TagEntry;
            const std::set<std::string> *m_FavoriteTags;

            Gdk::Color m_Color,
                       m_PrevColor;
            Glib::RefPtr<Gdk::Pixbuf> m_StarPixbuf,
                                      m_StarOutlinePixbuf;

            SignalNewTabTag m_SignalNewTabTag;
        };
    }
}

#endif /* _TAGVIEW_H_ */
