package repository.xml;

import domain.IDNota;
import domain.Nota;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import repository.InMemoryRepository;
import validators.Validator;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.*;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import java.io.IOException;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class NotaXMLRepository extends InMemoryRepository<IDNota, Nota> {
    private String fileName;

    public NotaXMLRepository(Validator validator, String fileName) {
        super(validator);
        this.fileName =fileName;
        loadData();
    }

    private void loadData(){
        try{
            Document document = DocumentBuilderFactory
                    .newInstance()
                    .newDocumentBuilder()
                    .parse(this.fileName);

            Element root = document.getDocumentElement();
            NodeList children = root.getChildNodes();
            for(int i=0; i<children.getLength(); i++){
                Node notaElement = children.item(i);
                if(notaElement instanceof Element){
                    Nota nota = createNotaFromElement((Element) notaElement);
                    super.save(nota);
                }
            }
        } catch (SAXException e) {
            e.printStackTrace();
        } catch (ParserConfigurationException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private Nota createNotaFromElement(Element notaElement) {
        String idStudent = notaElement.getAttribute("idStudent");
        String idTema = notaElement.getAttribute("idTema");
        String notaValue = notaElement.getElementsByTagName("value")
                .item(0)
                .getTextContent();
        String data = notaElement.getElementsByTagName("data")
                .item(0)
                .getTextContent();
        String profesor = notaElement.getElementsByTagName("profesor")
                .item(0)
                .getTextContent();

        Date date1 = null;
        try {
            date1 = new SimpleDateFormat("dd.MM.yyyy").parse(data);
        } catch (ParseException e) {
            e.printStackTrace();
        }

        Nota nota = new Nota(date1, Double.parseDouble(notaValue), profesor);
        IDNota idNota = new IDNota(Long.parseLong(idStudent), Long.parseLong(idTema));
        nota.setId(idNota);
        return nota;
    }

    @Override
    public Nota save(Nota entity) {
        Nota result = super.save(entity);
        if (result == null) {
            writeData();
        }
        return result;
    }

    @Override
    public Nota delete(IDNota id) {
        Nota result = super.delete(id);
        if(result != null){
            writeData();
        }
        return result;
    }

    @Override
    public Nota update(Nota entity) {
        Nota result = super.update(entity);
        if(result == null){
            writeData();
        }
        return result;
    }

    private void writeData() {
        try{
            Document document = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
            Element root = document.createElement("note");
            document.appendChild(root);
            for (Nota nota: findAll()) {
                Element e = createElementFromNota(document, nota);
                root.appendChild(e);
            }

            //write Document to file
            Transformer transformer = TransformerFactory.newInstance().newTransformer();
            Source source=new DOMSource(document);
            transformer.transform(source, new StreamResult(fileName));

        } catch (ParserConfigurationException | TransformerConfigurationException e) {
            e.printStackTrace();
        } catch (TransformerException e) {
            e.printStackTrace();
        }
    }

    private Element createElementFromNota(Document document, Nota nota) {
        Element element = document.createElement("nota");
        element.setAttribute("idStudent", nota.getId().getStudentId().toString());
        element.setAttribute("idTema", nota.getId().getTemaId().toString());

        Element notaValue = document.createElement("value");
        notaValue.setTextContent(new Double(nota.getValue()).toString());
        element.appendChild(notaValue);

        Element data = document.createElement("data");
        DateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy");
        String strDate = dateFormat.format(nota.getData());
        data.setTextContent(strDate);
        element.appendChild(data);

        Element profesor = document.createElement("profesor");
        profesor.setTextContent(nota.getProfesor());
        element.appendChild(profesor);

        return element;
    }

}
