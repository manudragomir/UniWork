package repository.xml;

import domain.Tema;
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

public class TemaXMLRepository extends InMemoryRepository<Long, Tema> {
    private String fileName;

    public TemaXMLRepository(Validator validator, String fileName) {
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
                Node temaElement = children.item(i);
                if(temaElement instanceof Element){
                    Tema tema = createTemaFromElement((Element) temaElement);
                    super.save(tema);
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

    private Tema createTemaFromElement(Element temaElement) {
        String id = temaElement.getAttribute("id");
        String startWeek = temaElement.getElementsByTagName("startWeek")
                .item(0)
                .getTextContent();
        String deadlineWeek = temaElement.getElementsByTagName("deadlineWeek")
                .item(0)
                .getTextContent();
        String descriere = temaElement.getElementsByTagName("descriere")
                .item(0)
                .getTextContent();


        Tema tema = new Tema(Integer.parseInt(deadlineWeek), descriere);
        tema.setStartWeek(Integer.parseInt(startWeek));
        tema.setId(Long.parseLong(id));
        return tema;
    }

    @Override
    public Tema save(Tema entity) {
        Tema result = super.save(entity);
        if (result == null) {
            writeData();
        }
        return result;
    }

    @Override
    public Tema delete(Long id) {
        Tema result = super.delete(id);
        if(result != null){
            writeData();
        }
        return result;
    }

    @Override
    public Tema update(Tema entity) {
        Tema result = super.update(entity);
        if(result == null){
            writeData();
        }
        return result;
    }

    private void writeData() {
        try{
            Document document = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
            Element root = document.createElement("teme");
            document.appendChild(root);
            for (Tema tema: findAll()) {
                Element e = createElementFromTema(document, tema);
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

    private Element createElementFromTema(Document document, Tema tema) {
        Element element = document.createElement("tema");
        element.setAttribute("id", tema.getId().toString());

        Element startWeek = document.createElement("startWeek");
        startWeek.setTextContent(new Integer(tema.getStartWeek()).toString());
        element.appendChild(startWeek);

        Element deadlineWeek = document.createElement("deadlineWeek");
        deadlineWeek.setTextContent(new Integer(tema.getDeadlineWeek()).toString());
        element.appendChild(deadlineWeek);

        Element descriere = document.createElement("descriere");
        descriere.setTextContent(tema.getDescriere());
        element.appendChild(descriere);

        return element;
    }

}
