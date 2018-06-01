#include "uiherramienta.h"
#include "ui_uiherramienta.h"
#include "qmessagebox.h"

UIHerramienta::UIHerramienta(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UIHerramienta)
{
    ui->setupUi(this);
    ui->botonResolver->setIcon(QIcon(":/iconos/right127.png"));
    ui->botonVaciar->setIcon(QIcon(":/iconos/close33.png"));
    ui->botonBorrar->setIcon(QIcon(":/iconos/circular194.png"));
    ui->botonCargar->setIcon(QIcon(":/iconos/approve9.png"));
    ui->botonValuaciones->setIcon(QIcon(":/iconos/search67.png"));
    ui->actionAbrir_Archivo->setIcon(QIcon(":/iconos/icono_abrir.png"));
    ui->actionGuardar_Archivo->setIcon(QIcon(":/iconos/icono_guardar.png"));
    ui->textBrowserInfo->hide();
    ui->toolBarInfo->hide();

    ui->espacio0->setFixedHeight(7);
    ui->espacio1->setFixedHeight(7);
    ui->botonResolver->setFixedHeight(30);
    ui->botonValuaciones->setFixedHeight(30);
    this->setFixedSize(650,400);
}

UIHerramienta::~UIHerramienta()
{
    delete ui;
}

void UIHerramienta::on_botonCargar_clicked()
{
    QString texto = ui->lineClausula->text();
    Clausula clausula;
    cargarClausula(texto, clausula);
    if (clausulaCorrecta(clausula))
    {
        QTextCursor c = ui->textBrowser->textCursor();
        QString vacio = "";
        QString t = ui->textBrowser->toPlainText();
        if (t == vacio)
        {
            c.insertText("{");
            c.insertText(texto);
        }
        else
        {
            c.insertText(" , ");
            c.insertText("{");
            c.insertText(texto);
        }
        c.insertText("}");
        conjunto.agregarClausula(clausula);
    }
    else
    {
        QMessageBox::warning(this,"Error","La clausula que intenta cargar no está correctamente definida");
    }
    ui->lineClausula->clear();
}

void UIHerramienta::on_botonResolver_clicked()
{
    if (! conjunto.vacio())
    {
        DavisPutnam * dpll = new DavisPutnam(conjunto,'h');
        dpll->resolver();
        dpll->show();
        this->close();
    }
    else
        QMessageBox::warning(this, "Error", "Por favor ingrese al menos una clausula para poder realizar la operacion deseada");
}

void UIHerramienta::cargarClausula(const QString & t, Clausula & c)
{
    QString literal = "";
    QString aux = t;
    aux.push_back(',');
    QString::const_iterator it = aux.begin();
    while (it != aux.end())
    {
        if (*it != ',')
            literal = literal + *it;
        else
        {
            Literal lit(literal);
            c.agregarLiteral(lit);
            literal = "";
        }
         it++;
    }
}

void UIHerramienta::CargaClausulasArchivo(QString mText)
{
    QString :: iterator Ite = mText.begin();
    while(Ite != mText.end())
    {
        Clausula C;
        if( *Ite == '{')
        {
            Ite++;
            QString Aux="";
            while((*Ite!='}') && (Ite!=mText.end()))
            {
                if(*Ite!=',')
                    Aux+=*Ite;
                else
                {
                    Literal L(Aux);
                    Aux="";
                    C.agregarLiteral(L);
                }
                Ite++;
                if(*Ite=='}')
                {
                    Literal L(Aux);
                    C.agregarLiteral(L);
                }
             }
            conjunto.agregarClausula(C);
            Ite++;
            C.vaciar();
        }
        while((*Ite!='{')&&(Ite!=mText.end()))
            Ite++;
    }
}

bool UIHerramienta::clausulaCorrecta(Clausula clausula)
{
    set<Literal> c = clausula.obtenerClausula();
    set<Literal>::const_iterator it = c.begin();
    while (it != c.end())
    {
        if (it->obtenerLiteral() == "")
            return false;
        else
            if (it->obtenerLiteral() == ",")
                return false;
        it++;
    }
    return true;
}

void UIHerramienta::on_botonNegacion_clicked()
{
    ui->lineClausula->insert("~");
}

void UIHerramienta::on_botonBorrar_clicked()
{
    Clausula clausula;
    QString stringConjunto = ui->textBrowser->toPlainText();
    QTextCursor cursor = ui->textBrowser->textCursor();
    QString ultimaClausula = "";
    if (stringConjunto != ultimaClausula)
    {
        QString::const_iterator it = stringConjunto.end();
        it--; it--;
        cursor.deletePreviousChar(); cursor.deletePreviousChar();
        while (*it != '{')
        {
            if (*it != ',')
                ultimaClausula.push_front(*it);
            else
            {
                Literal aux(ultimaClausula);
                clausula.agregarLiteral(aux);
                ultimaClausula = "";
            }
            it--;
            cursor.deletePreviousChar();
        }
    }
    cursor.deletePreviousChar(); cursor.deletePreviousChar(); cursor.deletePreviousChar();
    Literal aux(ultimaClausula);
    clausula.agregarLiteral(aux);
    conjunto.eliminarClausula(clausula);
}

void UIHerramienta::on_botonVaciar_clicked()
{
    conjunto.vaciarConjuntoClausulas();
    ui->textBrowser->clear();
}

void UIHerramienta::on_actionGuardar_Archivo_triggered()
{
    QString Clausulas = ui->textBrowser->toPlainText();
    if(Clausulas!="")
    {
        QString Filename = QFileDialog::getSaveFileName(this,tr("Save File"),QStandardPaths::locate(QStandardPaths::DesktopLocation,""),"Text File (*.txt)");
        QFile file(Filename);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream out(&file);
            out<<Clausulas;
            file.close();
        }
    }
    else
        QMessageBox::warning(this,"Atención.","No hay ninguna Clausula cargada.");
}

void UIHerramienta::on_actionAbrir_Archivo_triggered()
{
    QString Filename = QFileDialog::getOpenFileName(this,tr("Open File"),QStandardPaths::locate(QStandardPaths::DesktopLocation,""),"Text File (*.txt)");
        QFile file(Filename);

        QTextStream in(&file);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this,"Error."," No se pudo abrir el Archivo.",QMessageBox::Ok);
        }
       else{

        QString mText = in.readAll();
        file.close();
        if((mText[0]=='{') && (mText[mText.length()-1]=='}'))
        {
            this->hide();
            this->show();
            ui->textBrowser->clear();
            conjunto.vaciarConjuntoClausulas();
            QTextCursor c = ui->textBrowser->textCursor();
            c.insertText(mText);
            CargaClausulasArchivo(mText);
        }
        else
            QMessageBox::warning(this,"Error."," El Archivo no estaba generado correctamente.",QMessageBox::Ok);
    }
}

void UIHerramienta::on_actionQue_es_DPLL_triggered()
{
    ui->toolBar->hide();
    ui->toolBarInfo->show();
    ui->botonBorrar->hide();
    ui->botonCargar->hide();
    ui->botonNegacion->hide();
    ui->botonResolver->hide();
    ui->botonVaciar->hide();
    ui->labelClausula->hide();
    ui->labelConjunto->hide();
    ui->lineClausula->hide();
    ui->textBrowser->hide();
    ui->textBrowserInfo->show();
    ui->botonValuaciones->hide();
    ui->espacio0->hide();
    ui->espacio1->hide();
}

void UIHerramienta::on_actionAtras_triggered()
{
    MainWindow * w = new MainWindow();
    w->show();
    this->close();
}

void UIHerramienta::on_actionAtrasInfo_triggered()
{
    ui->toolBarInfo->hide();
    ui->toolBar->show();
    ui->botonBorrar->show();
    ui->botonCargar->show();
    ui->botonNegacion->show();
    ui->botonResolver->show();
    ui->botonVaciar->show();
    ui->labelClausula->show();
    ui->labelConjunto->show();
    ui->lineClausula->show();
    ui->textBrowser->show();
    ui->textBrowserInfo->hide();
    ui->botonValuaciones->show();
    ui->espacio0->show();
    ui->espacio1->show();
}

void UIHerramienta::on_botonValuaciones_clicked()
{
    if (! conjunto.vacio())
    {
        DavisPutnam * dpll = new DavisPutnam(conjunto,'h');
        dpll->generar_Valuaciones();
        dpll->mostrar_Valuaciones();
        this->close();
        dpll->show();
    }
    else
        QMessageBox::warning(this, "Error", "Por favor ingrese al menos una clausula para poder realizar la operacion deseada");
}
