#include "textbox.h"

TextBox::TextBox(QGraphicsItem* parent) {
    if(parent != nullptr){
        setParentItem(parent);
    }
    input = new QTextEdit();
    connect(input,SIGNAL(textChanged()),this,SLOT(textChanged()));
    input->setStyleSheet("background-color:transparent; border:none;");
    setWidget(input);
}


void TextBox::paint(QPainter *painter,
                    const QStyleOptionGraphicsItem *option,
                    QWidget *widget){
    if(painter && option && widget){
        if(!painter->isActive()) return;
        QStyleOptionGraphicsItem opts(*option);

        opts.state = QStyle::State_None;

        painter->setBrush(Qt::NoBrush);
        painter->setPen(Qt::NoPen);
        return QGraphicsProxyWidget::paint(painter, &opts, widget);
    }
    return;
}


bool TextBox::isAllowedCharacter(int c){
    if(c >= 48 && c <= 57){
        return true;
    }else if(c >= 65 && c <= 90){
        return true;
    }else if(c >= 97 && c <= 122){
        return true;
    } else if(c == 39 || c== 33 || c==34 || c==63 || c == 32){
        return true;
    }
    return false;
}

QString TextBox::getCurrentText(){
    return this->input->toPlainText();
}

QTextEdit* TextBox::getInput(){
    return this->input;
}

void TextBox::clearTextBox(){
    input->clear();
}


int TextBox::setTextLimit(int textLimit){
    this->textLimit = textLimit;
    return this->textLimit;
}
int TextBox::getTextLimit(){
    return this->textLimit;
}


void TextBox::textChanged(){
    if(textLimit != -1 && textLimit > 1 && input->toPlainText().size() > textLimit){
        QString msg = getCurrentText().first(textLimit);
        input->setText(msg);

        QTextCursor cursor(input->document());
        cursor.movePosition(QTextCursor::End);
        input->setTextCursor(cursor);
    }
    /*QTextDocument* doc = input->document();
    qreal totalHeight = 0;

    QTextBlock block = doc->begin();
    while (block.isValid()) {
        QTextLayout* layout = block.layout();
        int lineCount = layout->lineCount();

        QString prevLine = "";
        for (int i = 0; i < lineCount; ++i) {
            auto line = layout->lineAt(i);
            int lineText = line.textLength();
            int start = line.textStart();
            int length = line.textLength();
            QString newLine = block.text().mid(start, length);
            if(prevLine != newLine){
                totalHeight += line.height();
                prevLine = newLine;
            }
        }

        block = block.next();
    }*/

    input->setFixedHeight(input->document()->size().height());
}


bool TextBox::setCursorSetBeginning(bool cursorSetBeginning){
    this->cursorSetBeginning = cursorSetBeginning;
    return this->cursorSetBeginning;
}
bool TextBox::getCursorSetBeginning(){
    return this->cursorSetBeginning;
}

/*void TextBox::keyPressEvent(QKeyEvent *event){
    if(isAllowedCharacter(event->key()) && currentText.size() < 49){
        currentText += event->text();
        displayText.push_back(event->text());

        QFontMetrics metrics(font());
        QString updatedDisplayText = displayText;
        for(int i = 0; i < displayText.size(); i++){
            if(metrics.horizontalAdvance(updatedDisplayText) > textWidth()-15) {
                updatedDisplayText.removeAt(0);
                continue;
            }
        }
        displayText = updatedDisplayText;

        setPlainText(displayText);
        qDebug() << "CURRENT : " << currentText;
        qDebug() << "DISPLAY: " << displayText;

        QTextCursor cursor(document());
        cursor.setPosition(displayText.size());
        setTextCursor(cursor);
        event->accept();
    }else if(event->key() == Qt::Key_Backspace){
        currentText.removeAt(currentText.size()-1);

        QFontMetrics metrics(font());
        QString updatedDisplayText = "";
        for(int i = currentText.size()-1; i >= 0; i--){
            if(metrics.horizontalAdvance(updatedDisplayText) < textWidth()-15) {
                updatedDisplayText.push_front(currentText.at(i));
                continue;
            }
        }
        displayText = updatedDisplayText;
        setPlainText(displayText);
        qDebug() << "CURRENT : " << currentText;
        qDebug() << "DISPLAY: " << displayText;

        QTextCursor cursor(document());
        cursor.setPosition(displayText.size());
        setTextCursor(cursor);
        event->accept();
    }
}*/
