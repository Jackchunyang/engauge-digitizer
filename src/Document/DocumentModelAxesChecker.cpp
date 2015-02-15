#include "CmdMediator.h"
#include "DocumentModelAxesChecker.h"
#include "DocumentSerialize.h"
#include "Logger.h"
#include <QXmlStreamWriter>
#include "Xml.h"

const int DEFAULT_CHECKER_SECONDS = 3;

// Color that should be easily visible against black axes lines. Red resonates with
// the default axes point color, and seems fairly bright when opacity is made transparent.
const ColorPalette DEFAULT_LINE_COLOR = COLOR_PALETTE_RED;

DocumentModelAxesChecker::DocumentModelAxesChecker() :
  m_checkerMode (CHECKER_MODE_N_SECONDS),
  m_checkerSeconds (DEFAULT_CHECKER_SECONDS),
  m_lineColor (DEFAULT_LINE_COLOR)
{
}

DocumentModelAxesChecker::DocumentModelAxesChecker(const Document &document) :
  m_checkerMode (document.modelAxesChecker().checkerMode()),
  m_checkerSeconds (document.modelAxesChecker().checkerSeconds()),
  m_lineColor (document.modelAxesChecker().lineColor())
{
}

DocumentModelAxesChecker::DocumentModelAxesChecker(const DocumentModelAxesChecker &other) :
  m_checkerMode (other.checkerMode()),
  m_checkerSeconds (other.checkerSeconds()),
  m_lineColor (other.lineColor())
{
}

DocumentModelAxesChecker &DocumentModelAxesChecker::operator=(const DocumentModelAxesChecker &other)
{
  m_checkerMode = other.checkerMode();
  m_checkerSeconds = other.checkerSeconds();
  m_lineColor = other.lineColor();

  return *this;
}

CheckerMode DocumentModelAxesChecker::checkerMode() const
{
  return m_checkerMode;
}

int DocumentModelAxesChecker::checkerSeconds() const
{
  return m_checkerSeconds;
}

ColorPalette DocumentModelAxesChecker::lineColor () const
{
  return m_lineColor;
}

void DocumentModelAxesChecker::loadDocument(QXmlStreamReader &reader)
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelAxesChecker::loadDocument";

  QXmlStreamAttributes attributes = reader.attributes();

  if (attributes.hasAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_MODE) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_SECONDS) &&
      attributes.hasAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_LINE_COLOR)) {

    setCheckerMode ((CheckerMode) attributes.value(DOCUMENT_SERIALIZE_AXES_CHECKER_MODE).toInt());
    setCheckerSeconds (attributes.value(DOCUMENT_SERIALIZE_AXES_CHECKER_SECONDS).toInt());
    setLineColor ((ColorPalette) attributes.value(DOCUMENT_SERIALIZE_AXES_CHECKER_LINE_COLOR).toInt());

    // Read until end of this subtree
    while ((reader.tokenType() != QXmlStreamReader::EndElement) ||
    (reader.name() != DOCUMENT_SERIALIZE_AXES_CHECKER)){
      loadNextFromReader(reader);
    }
  } else {
    reader.raiseError ("Cannot read axes checker data");
  }
}

void DocumentModelAxesChecker::saveDocument(QXmlStreamWriter &writer) const
{
  LOG4CPP_INFO_S ((*mainCat)) << "DocumentModelAxesChecker::saveDocument";

  writer.writeStartElement(DOCUMENT_SERIALIZE_AXES_CHECKER);
  writer.writeAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_MODE, QString::number (m_checkerMode));
  writer.writeAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_SECONDS, QString::number (m_checkerSeconds));
  writer.writeAttribute(DOCUMENT_SERIALIZE_AXES_CHECKER_LINE_COLOR, QString::number (m_lineColor));
  writer.writeEndElement();
}

void DocumentModelAxesChecker::setCheckerMode(CheckerMode checkerMode)
{
  m_checkerMode = checkerMode;
}

void DocumentModelAxesChecker::setCheckerSeconds(int seconds)
{
  m_checkerSeconds = seconds;
}

void DocumentModelAxesChecker::setLineColor (ColorPalette lineColor)
{
  m_lineColor = lineColor;
}
