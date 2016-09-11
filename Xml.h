/************************************
 *Author:    Thomas Dost
 *Datum:     04.04.2015
 *Beschr.    Wrapper um tinyxml2 um einfachere Bedienung zu ermoeglichen
 *Changelog:
            Klasse ist nun Funktionsfaehig
            XmlElement hinzugefuegt
            Conversion Konstruktor fuer XmlElement hinzugefuegt
            Funktion aus tinyxml2 zu eigener Klasse hinzugefuegt
            --operator und ++ operator hinzugefuegt
            getValue hinzugefuegt
            isNull hinzugefuegt
            Code auskommentiert
            getNodeName hinzugefuegt.
 14.06.2016
            Programm beendet sich nun falls Datei nicht geladen werden kann.
            XmlElement operator[] hinzugefuegt
            XmlElement firstChildElelemt hinzugefuegt
            Xml rootElement hiznugefuegt
 15.06.2016
            Vermeindlichen CopyCtor hinzugeufuegt
            print() -> print() const
 15.08.2016
            Aus der Engine in CppGui kopiert
 22.08.2016
            Array Zugriffsoperator der Xml-Klasse ueberladen,
            Kommentare hinzugefuegt, die Array Zugriffsoperator callen jetzt
            die firstChild-Funktion ihrer Klasse.
            Konvertierungs Funktionen toFloat, toInt hinzugefuegt
            ----------------------------------------------------------
            XmlAttribute-Klasse hinzugefuegt
11.09.2016
            Als git submodule hinzugefuegt
            EngineType.h dependency removed
            Removed eng namespace
            Fixed indentation
            Moved using statements from global to local scope

 *TODO:
            Warum funktioniert der Parse Check nicht?
            Methoden der tinyxml XMLElement Klasse implementieren
                http://www.grinninglizard.com/tinyxml2docs/classtinyxml2_1_1_x_m_l_element.html
            Sichbarkeit anpassen
            Ueberlegen ob alle Klassen eine toXML Funktion erhalten mit
            der man sehr einfach den Inhalt dieser Klassen in einer Datei abspeichern kann,
            und ob man die dazu passende Ladefunktion hinzufuegen sollte.
            PreviousElement failt falls mNode nullptr ist
            wie soll das behandelt werden?gar nichts tun? oder Fehlermeldung? Gute Behandlung ausdenken!
 *************************************/
#pragma once
#include <string>
#include <iostream>

#include "tinyxml2/tinyxml2.h"
 


    class XmlAttribute
    {
        using namespace tinyxml2;
        using namespace std;
    };

    
    class XmlElement
    {
        using namespace tinyxml2;
        using namespace std;
    public:
        XmlElement(XMLElement& rhs)
        {
            mNode = &rhs;
        }
        
        
        /**********************************************
         *Descr:    Conversion Constructor fuer XMLElement Ptr die von allen tinyxml2 funktionen zurueckgegeben werden,
                    die mit XMLElelemt arbeiten
         *Param1:   Pointer auf ein XMLElement
         ***********************************************/
        XmlElement(XMLElement* rhs)
        {
            mNode = rhs;
        }
        
        
        /**********************************************
         *Descr:    Wert einer XML Node setzen
         *Param1:   Wert der gesetzt werden soll;
         ***********************************************/
        void setValue(const std::string& value)
        {
            mNode->SetText(value.c_str());
        }
        void setValue(const double value)
        {
            setValue(std::to_string(value));
        }
        void setValue(const int value)
        {
             setValue(std::to_string(value));
        }
        
        
        /**********************************************
         *Descr:    Funktion um auf Elementinhalt zu zugreifen
         *Ret:      Falls mNode == nullptr -> leerer String, sonst Inhalt des Elements
         ***********************************************/
        std::string getValue() const
        {
            if(mNode != nullptr)
            {
                return mNode->GetText();
            }
            return "";
        }
        
        
        /**********************************************
         *Descr:    Funktion um auf Namen einer Node zu aendern
         ***********************************************/
        void setName(const std::string& name)
        {
            if(mNode != nullptr)
            {
                mNode->SetName(name.c_str());
            }
            
        }
        
        
        /**********************************************
         *Descr:    Funktion um auf Nodename zu zugreifen
         *Ret:      Falls mNode == nullptr -> leerer String, sonst Name der Node auf die gezeigt wird
         ***********************************************/
        std::string getNodeName() const
        {
            if(mNode != nullptr)
            {
                return mNode->Value();
            }
            return "";
        }
        
        
        /**********************************************
         *Descr:    Setzt den mNode auf das naechste Xml Element auf gleicher Ebene.
         *Ret:      Das naechste Element auf gleicher Ebene, falls keine Element vorhanden ist wird mNode zu einen nullptr
         ***********************************************/
        XmlElement& operator++()
        {
            mNode = mNode->NextSiblingElement();
            return *this;
        }
        
        
        /**********************************************
         *Descr:    Setzt den mNode auf das vorherige Xml Element auf gleicher Ebene.
         *Ret:      Das voherige Element auf gleicher Ebene, falls keine Element vorhanden ist wird mNode zu einen nullptr
         ***********************************************/
        XmlElement& operator--()
        {
            mNode = mNode->PreviousSiblingElement();
            return *this;
        }
        
        
        /**********************************************
         *Descr:    Checkt ob mNode auf ein Xml Element zeigt
         *Ret:      True falls auf ein Element gezeigt wird, sonst false.
         ***********************************************/
        bool isNotNull() const
        {
            if(mNode == nullptr)
            {
                return false;
            }
            return true;
        }


        /**********************************************
        *Descr:    Wenn kein Argument mitgegeben wurde dann gibt die Funktion das erste 
                   Element des Baums zurueck, sonst das Element der derzeitigen Ebene mit dem uebergebenen Identifier.  
        *Param1:   Zu suchen Identifier
        *Ret:      Referenz auf das Element mit Namen ident
        ***********************************************/
        XmlElement firstChildElement(const std::string& ident = "")
        {
            return mNode->FirstChildElement(ident.c_str());
        }
        

        /**********************************************
        *Descr:    Wenn kein Argument mitgegeben wurde dann gibt die Funktion das erste 
                   Element des Baums zurueck, sonst das Element der derzeitigen Ebene mit dem uebergebenen Identifier.  
        *Param1:   Zu suchen Identifier
        *Ret:      Referenz auf das Element mit Namen ident
        ***********************************************/
        XmlElement operator[](const std::string& ident )
        {
            return firstChildElement(ident);
        }

         /**********************************************
        *Descr:    Konvertiert den derzeitigen Xml-Wert der ein Strings ist zu einem Float  
        *Ret:      Wert als float
        ***********************************************/
        float toFloat()
        {
            return std::stof(getValue());
        }
        /**********************************************
        *Descr:    Konvertiert den derzeitigen Xml-Wert der ein Strings ist zu einem int  
        *Ret:      Wert als int
        ***********************************************/
        int toInt()
        {
            return std::stoi(getValue());
        }
    public:
        XMLElement* mNode;
       
    };
    
    
    
    class Xml
    {
    using namespace tinyxml2;
    using namespace std;
    public:
        /**********************************************
         *Descr:   Konstruktor um ein Xml Dokument zu laden
         ***********************************************/
        Xml(filepath filepath) : mPath(filepath)
        {
            //Checkt ob das Dokument geladen werden konnte
            if(mDoc.LoadFile(filepath.c_str()) == XML_NO_ERROR)
            {
            //                    if(mDoc.Parse(filepath.c_str()) == XML_NO_ERROR)
            //                    {
                
            //                    }
            //                    else
            //                    {
            //                        std::cerr << "Die Datei:" << filepath << " konnte nicht GEPARSED werden" <<"|Error:"<< mDoc.ErrorID() <<std::endl;
                                  
            //                    }
            }
            else
            {
                std::cerr << "Die Datei:" << filepath.c_str() << " konnte nicht GELADEN werden" <<"|Error:"<< mDoc.ErrorID() <<std::endl;
                //Programm beenden
                exit(-1);
            }
        }
        ~Xml()
        {
            ;
        }
        /**********************************************
        *Descr:    Copy Konstruktor
        ***********************************************/
//        Xml(const Xml& rhs) :
//        mPath(rhs.mPath)
//        {
//            mDoc.s   rhs.mDoc.GetDocument();
//            print();
//        }
        
        
        /**********************************************
         *Descr:    Gibt das ganze Xml Dokument aus
         ***********************************************/
        void print() const
        {
            mDoc.Print();
        }
        /**********************************************
         *Descr:    Speichert das XmlDokument
         ***********************************************/
        bool saveFile()
        {
            mDoc.SaveFile(mPath.c_str());
        }
       
        
        XmlElement rootElement()
        {
            XmlElement temp = mDoc.RootElement();
            return temp.mNode;
        }
        /**********************************************
        *Descr:    Wenn kein Argument mitgegeben wurde dann gibt die Funktion das erste 
                   Element des Baums zurueck, sonst das Element der derzeitigen Ebene mit dem uebergebenen Identifier.  
        *Param1:   Zu suchen Identifier
        *Ret:      Referenz auf das Element mit Namen ident
        ***********************************************/
        XmlElement firstChildElement(const std::string& ident = "")
        {
            return mDoc.FirstChildElement(ident.c_str());
        }

        /**********************************************
        *Descr:    Wenn kein Argument mitgegeben wurde dann gibt die Funktion das erste 
                   Element des Baums zurueck, sonst das Element der derzeitigen Ebene mit dem uebergebenen Identifier.  
        *Param1:   Zu suchen Identifier
        *Ret:      Referenz auf das Element mit Namen ident
        ***********************************************/
        XmlElement operator[](const std::string& ident)
        {
            return firstChildElement(ident);
        }
    public:
        XMLDocument mDoc;
        filepath mPath;
    };


   