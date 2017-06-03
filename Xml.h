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
20.01.2017
            saveFiles gibt jetzt einen Statuswert zurueck ob das Speichern erfolgreich war.
            XmlElement operator[] benutzt jetzt XmlElement::firstChildNode stat tinyxml2::firstChildNote
            const XMLDocument& getTmxDoc() const hinzugefuegt
01.02.2017
            XmlElement(XMLElement& rhs) geloescht
             using  filepath = const std::string&, using int32 = int_fast32_t hinzugefuegt damit die Header bis auf
             tinyXml2 eigenstaendig ist.

*TODO:
            Methoden der tinyxml XMLElement Klasse implementieren
                http://www.grinninglizard.com/tinyxml2docs/classtinyxml2_1_1_x_m_l_element.html
            Sichbarkeit anpassen
            Ueberlegen ob alle Klassen eine toXML Funktion erhalten mit
            der man sehr einfach den Inhalt dieser Klassen in einer Datei abspeichern kann,
            und ob man die dazu passende Ladefunktion hinzufuegen sollte.
            PreviousElement failt falls mNode nullptr ist
            wie soll das behandelt werden?gar nichts tun? oder Fehlermeldung? Gute Behandlung ausdenken!
            toInt(), toDouble(), to... implementieren.
            CopyCtr, copy assign ctor fuer XmlElement. Xml schreiben falls moeglich, vielleicht auch den move ctor
            Xml Arguemnts support
            Tests prorammieren
            Component Xml iterieren
 *************************************/

/***************************************************
 *
 ***************************************************/


#pragma once
#include <string>
#include <iostream>

#include "tinyxml2/tinyxml2.h"


namespace eng
{
    using namespace tinyxml2;

    using  filepath = const std::string&;
    using int32 = int_fast32_t;
    /*! A test class, document with cmake*/
    class XmlElement
    {
    public:
        /********************************************//**
         *Conversion Constructor fuer XMLElement Ptr die von allen tinyxml2 funktionen zurueckgegeben werden,
                    die mit XMLElelement arbeiten
         *@param   Pointer auf ein XMLElement
         ***********************************************/
        XmlElement(XMLElement* rhs)
        {
            mNode = rhs;
        }

        
        /********************************************//**
         *Wert einer XML Node setzen
         *@param   Wert der gesetzt werden soll;
         ***********************************************/
        void setValue(const std::string& value)
        {
            mNode->SetText(value.c_str());
        }
        void setValue(const double value)
        {
            setValue(std::to_string(value));
        }
        void setValue(const int32 value)
        {
             setValue(std::to_string(value));
        }
        
        
        /**********************************************//**
         *Funktion um auf Elementinhalt zu zugreifen
         *\return Falls mNode == nullptr -> leerer String, sonst Inhalt des Elements
         ***********************************************/
        const std::string getValue() const
        {
            if(mNode != nullptr)
            {
                return mNode->GetText();
            }
            return "";
        }
        
        
        /**********************************************//**
         *Funktion um auf Namen einer Node zu aendern
         ***********************************************/
        void setName(const std::string& name)
        {
            if(mNode != nullptr)
            {
                mNode->SetName(name.c_str());
            }
            
        }
        
        
        /*********************************************//**
         *Funktion um auf Nodename zu zugreifen
         *\return Falls mNode == nullptr -> leerer String, sonst Name der Node auf die gezeigt wird
         ***********************************************/
        const std::string getElemName() const
        {
            if(mNode != nullptr)
            {
                return mNode->Name();
            }
            return "";
        }
        
        
        /**********************************************//**
         *Setzt den mNode auf das naechste Xml Element auf gleicher Ebene.
         *\return Das naechste Element auf gleicher Ebene, falls keine Element vorhanden ist wird mNode zu einen nullptr
         ***********************************************/
        XmlElement& operator++()
        {
            mNode = mNode->NextSiblingElement();
            return *this;
        }
        
        
        /**********************************************//**
         *Setzt den mNode auf das vorherige Xml Element auf gleicher Ebene.
         *\return Das voherige Element auf gleicher Ebene, falls keine Element vorhanden ist wird mNode zu einen nullptr
         ***********************************************/
        XmlElement& operator--()
        {
            mNode = mNode->PreviousSiblingElement();
            return *this;
        }
        
        
        /********************************************//**
         *Checkt ob mNode auf ein Xml Element zeigt
         *\return True falls auf ein Element gezeigt wird, sonst false.
         ***********************************************/
        bool isNotNull() const
        {
            if(mNode == nullptr)
            {
                return false;
            }
            return true;
        }

        /********************************************//**
        ***********************************************/
        const XmlElement firstChildElement(const std::string& ident = "") const
        {
            //Um die funktionsweise von tinyXml2 zu simulieren
            //muss beim Fehlen eines Elem. Names eine 0 uebergeben werden.
            if(ident == "")
                return mNode->FirstChildElement(nullptr);
            return mNode->FirstChildElement(ident.c_str());
        }


        /********************************************//**
        ***********************************************/
        const XmlElement operator[](const std::string& ident) const
        {
            return firstChildElement(ident);
        }

        /********************************************//**
        ***********************************************/
        XMLElement* getXMLElement()
        {
            return mNode;
        }
    private:
        XMLElement* mNode;
       
    };
    
    

    /******************************************************************************************************************************************
    *******************************************************************************************************************************************
    *******************************************************************************************************************************************/

    /*!Klasse zum einfacheren Verwalten von XML Dateien
    
    Diese Klasse ermöglicht das Öffnen, Schließen und Bearbeiten vom XML Dateien

    */
    class Xml
    {
    public:

        /*************************************************//**
         *Standart Konstruktor, zum initialiseren der Klasese wird in disem Fall
         *die init() Methode verwendet
        ***************************************************/
        Xml() {}

        /************************************************//**
         *Konstruktor um ein Xml Dokument zu laden
         *************************************************/
        Xml(filepath filepath) : mPath(filepath)
        {
            //Checkt ob das Dokument geladen werden konnte

            if(mDoc.LoadFile(filepath.c_str())  != XML_ERROR_FILE_NOT_FOUND)
            {
                //TODO Sowohl bei Erfolg als auch bei Fehler sollte keine Nachricht aussgegeben sondern was anderes gemacht werden
                std::cout << "Die Datei:" << filepath << " ERFOLGREICH geladen werden" << std::endl;
            }
            else
            {
                std::cerr << "Die Datei:" << filepath << " konnte nicht GELADEN werden" << std::endl;
                //Programm beenden
                exit(-1);
            }
        }


        bool init(filepath filepath)
        {
            //Checkt ob das Dokument geladen werden konnte
            if(mDoc.LoadFile(filepath.c_str()) != XML_ERROR_FILE_NOT_FOUND)
            {
                mPath = filepath;
                //TODO Sowohl bei Erfolg als auch bei Fehler sollte keine Nachricht aussgegeben sondern was anderes gemacht werden
                return true;
            }
            else
            {
                return false;
            }
        }

        /**********************************************
        *Copy Konstruktor
        ***********************************************/
//        Xml(const Xml& rhs) :
//        mPath(rhs.mPath)
//        {
//            mDoc.s   rhs.mDoc.GetDocument();
//            print();
//        }
        
        
        /********************************************//**
         *Gibt das ganze Xml Dokument aus
         ***********************************************/
        void print() const
        {
            mDoc.Print();
        }
        /********************************************//**
         *    Speichert das XmlDokument
         ***********************************************/
        bool saveFile()
        {
            return mDoc.SaveFile(mPath.c_str());

        }

        /**********************************************
        *Gibt das rootElement zurueck
        *\return RootElement aka das Element auf hoechster Ebene
        *Beispiel
        *<options>
        *     <resX>1920</resX>
        *     <resY>1200</resY>
        *</options>
        *Returnwert waere options
        ***********************************************/
         XmlElement rootElement()
        {
            XmlElement temp = mDoc.RootElement();
            return temp;
        }


        const XMLDocument& getTmxDoc() const
        {
            return mDoc;
        }

    private:
        XMLDocument mDoc;
        std::string mPath;
    };
}


/*  ATTRIBUTES BEIIIIIIISPIEL
eng::XmlElement test1 = xml.mDoc.FirstChildElement( "options" )->FirstChildElement("note");
 std::cout << test1.getNodeName() <<   test1.mNode->FirstAttribute()->Name() <<std::endl;
 */