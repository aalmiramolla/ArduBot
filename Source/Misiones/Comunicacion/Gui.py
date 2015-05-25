#!/usr/bin/env python
# -*- coding: utf-8 -*-

from gi.repository import Gtk

class GuiGTK:
    def __init__(self):
        self.gladefile = "Gui.glade"
        self.glade = Gtk.Builder()
        self.glade.add_from_file(self.gladefile)
        self.glade.connect_signals(self)

        # Nombres de las misiones
        self.misiones = ['Mision 1_1', 'Mision 1_2', 'Mision 1_3']
        self.misiones_combo = self.glade.get_object('comboboxMisiones')
        self.misiones_combo.set_entry_text_column(0)
        for name in self.misiones:
            self.misiones_combo.append_text(name)

        self.glade.get_object("window1").show_all()

    def on_window1_delete_event(self, widget, event):
        Gtk.main_quit()

    def comboboxMisiones_changed(self, combo):
        self.misiones_inst = self.glade.get_object('textview1')
        buffer = self.misiones_inst.get_buffer()
        print (combo.get_active_text())
        if combo.get_active_text()==self.misiones[0]:
            buffer.set_text(open('mision1', 'r').read())
        elif combo.get_active_text()==self.misiones[1]:
            buffer.set_text("Hola estoy en la mision 2")
        elif combo.get_active_text()==self.misiones[2]:
            buffer.set_text("Hola estoy en la mision 3")

    def lanzarMision_cliked(self, widget):
        print ('Lanzo la mision')


if __name__ == "__main__":
    try:
        gg = GuiGTK()
        Gtk.main()
    except KeyboardInterrupt:
        pass
