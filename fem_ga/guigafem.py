#!/usr/bin/env python

# guifemga.py
import os, signal,threading, locale, gtk, time
import pygtk
import commands
from pickle import load, dump
pygtk.require('2.0')
import gtk
import sys, string
import subprocess, threading
import time
gtk.gdk.threads_init()

codificacion = locale.getpreferredencoding()
utf8conv = lambda x : unicode(x, codificacion).encode('utf8')

PATHREADMESH	='../femga0.0.1/readmesh/readmesh/Debug/'
READMESH	='readmesh '

PATHMALLA	=' ../femga0.0.1/files/' 
MALLA		='malla8.mesh'

PATHGA		='/media/mountpoint/U12010/Tesis/FEMGA/femga0.0.1/ga/gafem/Debug'
GA		='/gafem'

STOP		= 0

def exec_readmesh(label):
	comando = PATHREADMESH + READMESH + label.get_text()
	salida = commands.getoutput(comando)
	return salida 




class GuiFemGa:


    # Our new improved callback.  The data passed to this method
    # is printed to stdout.
    def callback(self, widget, data):
        print "Hello again - %s was pressed" % data

    # another callback
    def delete_event(self, widget, event, data=None):
        gtk.main_quit()
        return False
    def llamargmsh(self,widget,labelnombremalla):
	commands.getoutput("gmsh "+labelnombremalla.get_label())

    def threadweitega(self,widget,textview,buffer_texto,buttonstopga,labelnombremalla,labelmejor,labelpromedioga,labelpeor, entry_gen,entry_cro,entry_mut):	
	hilo=threading.Thread(target=self.writega, args=(textview,buffer_texto,buttonstopga,labelnombremalla,labelmejor,labelpromedioga,labelpeor,entry_gen,entry_cro,entry_mut))
	hilo.start()
    
    def threadstopgoga(self,widget,buttonstopga):
    	hilo=threading.Thread(target=self.stopgoga,args=(buttonstopga))
    	hilo.start()
    	  
    def stopgoga(self,buttonstopga):
    	pid = commands.getoutput("pidof gafem")
     	gtk.gdk.threads_enter()
    	if buttonstopga.get_label() == "Stop":	 
    		os.kill(int(pid), signal.SIGSTOP)
    		buttonstopga.set_label("GO")
	
	if buttonstopga.get_label() == "Go":
		os.kill(int(pid), signal.SIGCONT)
		buttonstopga.set_label("Stop")
    	gtk.gdk.threads_leave()		
       	
    			 

    def writega(self,textview,buffer_texto,buttonstopga,labelnombremalla,labelmejor,labelpromedioga,labelpeor, entry_gen,entry_cro,entry_mut):
	stdin, stdouterr = os.popen4('/media/mountpoint/U12010/Tesis/FEMGA/femga0.0.1/ga/gafem/Debug/gafem '+labelnombremalla.get_label()+' '+entry_gen.get_text()+' '+entry_cro.get_text()+' '+entry_mut.get_text())
	auxlineamejor = ""
	auxpromedio = ""
	auxpeor = ""
	while 1:
		lineamejor = ""
		lineapromedio = ""
		lineapeor = ""
		linea = ""
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()				
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline() 
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()  
		linea=linea+stdouterr.readline()
		linea=linea+stdouterr.readline()
		lineamejor=stdouterr.readline()
		lineapromedio = stdouterr.readline()
		lineapeor = stdouterr.readline()
		if not lineamejor:
			labelmejor.set_label(auxlineamejor)
		else:
			labelmejor.set_label(lineamejor) 
			auxlineamejor = lineamejor			
		if not 	lineapromedio:
			labelpromedioga.set_label(auxpromedio)	
		else:
			labelpromedioga.set_label(lineapromedio)
			auxpromedio = lineapromedio			
		if not  lineapeor:
			labelpeor.set_label(auxpeor)	
		else:
			labelpeor.set_label(lineapeor)
			auxpeor = lineapeor			
		if not linea:
			break 
		gtk.gdk.threads_enter()		
		iter = buffer_texto.get_end_iter()
		buffer_texto.place_cursor(iter)
		buffer_texto.insert(iter,utf8conv(linea))
		textview.scroll_to_mark(buffer_texto.get_insert(),0.1)
		gtk.gdk.threads_leave()
		#time.sleep(0.3)



    def calcularcalidad(self,widget,labelnombremalla, labelvalorcalidad):
	salidareadmesh = exec_readmesh(labelnombremalla)
	
	print salidareadmesh
	labelvalorcalidad.set_text(salidareadmesh)

    def calculafem(self,widget,labelnombremalla):
    	resultadofem = commands.getoutput("/media/mountpoint/U12010/Tesis/FEMGA/femga0.0.1/fem/fem/Debug/fem "+labelnombremalla.get_text())
    	print resultadofem
    
    def verresultadofem(self,widget,labelnombremalla):
    	archivo = labelnombremalla.get_text()
    	archivo = archivo.rstrip()
    	archivo = archivo+str(".fem")
    	comando = "geany " + archivo
    	print comando
    	commands.getoutput(comando)
    	
    
    def selectfile(self,widget,labelnombremalla):
	dialog = gtk.FileChooserDialog("Open..",
                               None,
                               gtk.FILE_CHOOSER_ACTION_OPEN,
                               (gtk.STOCK_CANCEL, gtk.RESPONSE_CANCEL,
                                gtk.STOCK_OPEN, gtk.RESPONSE_OK))
	dialog.set_default_response(gtk.RESPONSE_OK)

	filter = gtk.FileFilter()
	filter.set_name("All files")
	filter.add_pattern("*")
	dialog.add_filter(filter)

	filter = gtk.FileFilter()
	dialog.add_filter(filter)

	response = dialog.run()
	if response == gtk.RESPONSE_OK:
	    print dialog.get_filename(), 'selected'
	    archivo = dialog.get_filename()
	elif response == gtk.RESPONSE_CANCEL:
	    print 'Closed, no files selected'
	dialog.destroy()



	labelnombremalla.set_text(archivo+"    ")	


    def __init__(self):

        # Create a new window
        self.window = gtk.Window(gtk.WINDOW_TOPLEVEL)
	
        # This is a new call, which just sets the title of our
        # new window to "Hello Buttons!"
        self.window.set_title("Metodo de Elementos Finitos - Algoritmo Genetico")
	self.window.set_default_size(1280, 600) 
        # Here we just set a handler for delete_event that immediately
        # exits GTK.
        self.window.connect("delete_event", self.delete_event)

        # Sets the border width of the window.
        self.window.set_border_width(10)
        
        # We create a vertical box (vbox) to pack the horizontal boxes into.
        # This allows us to stack the horizontal boxes filled with buttons one
        # on top of the other in this vbox.
        box_principal = gtk.VBox(False, 0)

    	boxmalla = gtk.HBox(False, 0)
	
    	# create a new label.
    	labelnombremalla = gtk.Label(" malla                                                                            ") 
        
    	# Align the label to the left side.  We'll discuss this method
    	# and others in the section on Widget Attributes.
    	labelnombremalla.set_alignment(0, 0)

    	# Pack the label into the vertical box (vbox box1).  Remember that 
    	# widgets added to a vbox will be packed one on top of the other in
    	# order.
    	boxmalla.pack_start(labelnombremalla, False, False, 0)

    	# Show the label
    	labelnombremalla.show()


    	# 
    	buttonselecmalla = gtk.Button("Seleccionar malla")

	buttonselecmalla.connect("clicked",self.selectfile,labelnombremalla)
    	boxmalla.pack_start(buttonselecmalla, False, False, 0)
    	buttonselecmalla.show()

	# create a new label.
    	labelvalorcalidad = gtk.Label(" 0.0  ")

	buttoncalculacalidad = gtk.Button("Calcular calidad")
	buttoncalculacalidad.connect("clicked",self.calcularcalidad,labelnombremalla, labelvalorcalidad)
	boxmalla.pack_start(buttoncalculacalidad, False, False, 0)
	buttoncalculacalidad.show()

	
    	# create a new label.
    	labelcalidad = gtk.Label(" Calidad :  ")
        
    	# Align the label to the left side.  We'll discuss this method
    	# and others in the section on Widget Attributes.
    	labelcalidad.set_alignment(0, 0)

    	# Pack the label into the vertical box (vbox box1).  Remember that 
    	# widgets added to a vbox will be packed one on top of the other in
    	# order.
    	boxmalla.pack_start(labelcalidad, False, False, 0)

    	# Show the label
    	labelcalidad.show()	
        
    	# Align the label to the left side.  We'll discuss this method
    	# and others in the section on Widget Attributes.
    	labelvalorcalidad.set_alignment(0, 0)

    	# Pack the label into the vertical box (vbox box1).  Remember that 
    	# widgets added to a vbox will be packed one on top of the other in
    	# order.
    	boxmalla.pack_start(labelvalorcalidad, False, False, 0)

    	# Show the label
    	labelvalorcalidad.show()
 
    	# 
    	buttonvermalla = gtk.Button(" Ver malla ")
	buttonvermalla.connect("clicked",self.llamargmsh,labelnombremalla)
    	boxmalla.pack_end(buttonvermalla, False, False, 0)
    	buttonvermalla.show()

	box_principal.pack_start(boxmalla, False, False, 0)
	boxmalla.show()

	# Creates a separator, we'll learn more about these later, 
        # but they are quite simple.
        separator = gtk.HSeparator()
	
        # Pack the separator into the vbox. Remember each of these
        # widgets is being packed into a vbox, so they'll be stacked
        # vertically.
        box_principal.pack_start(separator, False, True, 5)
        separator.show()

	############################################################################################

	# Box Algoritmo Genetico
	sw = gtk.ScrolledWindow()
	sw.set_policy(gtk.POLICY_AUTOMATIC, gtk.POLICY_AUTOMATIC)
	
        boxga = gtk.HBox(False, 0) 

	boxview = gtk.HBox(False,0)
	boxcalidadstopga = gtk.HBox(False,0)
	boxvaloresga = gtk.VBox(False,0)
    	textview = gtk.TextView()
    	boxviewvalores = gtk.HBox(False,0)
    	 

    	boxview.set_size_request(1000, 320) 
	buffer_texto = textview.get_buffer()  
	
	sw.add(textview) 
	 
        buttonga = gtk.Button("  GA  ")
        label_gen = gtk.Label("Generaciones : ")
        entry_gen = gtk.Entry(20)
        label_cro = gtk.Label("Porcentage de Crossover : ")
        entry_cro = gtk.Entry(20)
        label_mut = gtk.Label("Porcentage de Mutacion : ")
        entry_mut = gtk.Entry(20)
        
	buttonstopga = gtk.Button("Stop")
	commanddo= " ls "

        
        buttonstopga.connect("clicked",self.threadstopgoga,buttonstopga) 
        
	labelpromedioga = gtk.Label("Promedio : ")
	boxvaloresga.pack_start(labelpromedioga,True,False,0) 
	labelpeor = gtk.Label("Peor Cromosoma : ")
	
	labelmejorga = gtk.Label("Mejor Cromosoma: ")
	
	boxvaloresga.pack_start(labelmejorga,True,False,0) 
	boxvaloresga.pack_start(labelpeor,True,False,0)
	buttonga.connect("clicked",self.threadweitega,textview,buffer_texto,buttonstopga,labelnombremalla,labelmejorga,labelpromedioga,labelpeor,entry_gen,entry_cro,entry_mut)  
	
	labelcalidadga = gtk.Label(" Calidad :  ")
	boxcalidadstopga.pack_start(labelcalidadga,True,False,0)
	boxcalidadstopga.pack_start(buttonstopga,True,False,0)
        boxga.pack_start(buttonga, True, False, 0)
        boxga.pack_start(label_gen, True, False, 0)
        boxga.pack_start(entry_gen, True, False, 0)
        boxga.pack_start(label_cro, True, False, 0)
        boxga.pack_start(entry_cro, True, False, 0)
        boxga.pack_start(label_mut, True, False, 0)
        boxga.pack_start(entry_mut, True, False, 0)
        
        boxview.pack_start(sw)
	#boxview.pack_start(textview,True,False,0)
	#boxview.pack_end(boxvaloresga,True,False,0)
	sw.show()
        # pack the quitbox into the vbox (box1)
        
	
	boxviewvalores.pack_start(boxview,True,False,0)
	
	boxviewvalores.pack_end(boxvaloresga, True, False, 0)
	
        box_principal.pack_start(boxga, True, False, 0)
        box_principal.pack_start(boxviewvalores, True, False, 0)
    	
	
	# And show everything left
        buttonga.show()
        entry_gen.show()
        entry_cro.show()
        entry_mut.show()
        label_gen.show()
        label_cro.show()
        label_mut.show()
        boxga.show()
	boxview.show()
	boxviewvalores.show()
    	textview.show()
	boxvaloresga.show()
	labelpromedioga.show()
	labelpeor.show()
	labelmejorga.show()
	
	labelcalidadga.show()
	buttonstopga.show()
 	

	#self.writegadefault(self,textview)
	#############################################################################################


	boxfem1 = gtk.HBox(False,0)
	boxfem2 = gtk.VBox(False,0)
	boxfem3 = gtk.VBox(False,0)
	boxfem4 = gtk.VBox(False,0)
	boxfem5 = gtk.VBox(False,0)

	labelnada = gtk.Label(" ")
	labeliel1 = gtk.Label(" Elemento malla 1  ")
	labeliel1valor = gtk.Label(" i  ")
	labelsumerr1 = gtk.Label(" suma error :  ")
	labelsumerr1valor = gtk.Label(" 0.0  ")


	labeliel2 = gtk.Label(" Elemento malla 2   ")
	labeliel2valor = gtk.Label(" j  ")
	labelsumerr2 = gtk.Label(" suma error :  ")
	labelsumerr2valor = gtk.Label(" 0.0  ")
	buttonfem = gtk.Button("  Resultado  ")
	buttonfem.connect("clicked",self.verresultadofem,labelnombremalla)

	
	labelec = gtk.Label(" Ec. Diferencial :  ")
	labelecvalor = gtk.Label(" x*y  ")
	labelsumerrvalor = gtk.Label(" d2U/dx + d2U/dy = 0 ")
	buttongid1 = gtk.Button("  FEM  ")
	
	buttongid1.connect("clicked",self.calculafem,labelnombremalla)
	buttongid2 = gtk.Button("  Gid 2  ")



	


	#boxfem2.pack_start(labeliel1,True,False,0)
	#boxfem2.pack_start(labeliel2,True,False,0)
	boxfem2.pack_start(labelec,True,False,0)


	#boxfem3.pack_start(labelsumerr1,True,False,0)
	#boxfem3.pack_start(labelsumerr2,True,False,0)
	boxfem3.pack_start(labelsumerrvalor,True,False,0)
	
	
	boxfem4.pack_start(buttongid1,True,False,0)
	boxfem4.pack_end(labelnada,True,False,0)
	
	boxfem5.pack_start(buttonfem,True,False,0)
	#boxfem5.pack_start(buttongid2,True,False,0)
	
	boxfem1.pack_start(boxfem2,True,False,0)
	boxfem1.pack_start(boxfem3,True,False,0)
	boxfem1.pack_start(boxfem4,True,False,0)
	boxfem1.pack_start(boxfem5,True,False,0)
	
	
	
	box_principal.pack_end(boxfem1,False,False,0)
	
	
	separator = gtk.HSeparator()
	box_principal.pack_end(separator, False, True, 5)
        separator.show()
        box_principal.pack_end(boxcalidadstopga,False,False,0)
	boxcalidadstopga.show()
        
	labelnada.show()
	#labeliel1.show()
	labeliel1valor.show()
	#labelsumerr1.show()
	labelsumerr1valor.show()


	#labeliel2.show()
	labeliel2valor.show()
	#labelsumerr2.show()
	labelsumerr2valor.show()
	buttonfem.show()


	
	labelec.show()
	labelecvalor.show()
	labelsumerrvalor.show()
	buttongid1.show() 
	#buttongid2.show()

	buttonfem.show()
	boxfem1.show()
	boxfem2.show()
	boxfem3.show()
	boxfem4.show()
	boxfem5.show()
	
	###############################################################################################
        # Pack the vbox (box1) which now contains all our widgets, into the
        # main window.
        self.window.add(box_principal) 
    
        box_principal.show()
        # Showing the window last so everything pops up at once.
        self.window.show()      


def main():
    gtk.main()

if __name__ == "__main__":
    hello = GuiFemGa()
    main()
   

