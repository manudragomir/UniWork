package repository.xml;

import domain.Student;
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

public class StudentXMLRepository extends InMemoryRepository<Long, Student> {
    private String fileName;

    public StudentXMLRepository(Validator validator, String fileName) {
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
                Node studentElement = children.item(i);
                if(studentElement instanceof Element){
                    Student student = createStudentFromElement((Element) studentElement);
                    super.save(student);
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

    private Student createStudentFromElement(Element studentElement) {
        String id = studentElement.getAttribute("id");
        String nume = studentElement.getElementsByTagName("nume")
                .item(0)
                .getTextContent();
        String prenume = studentElement.getElementsByTagName("prenume")
                .item(0)
                .getTextContent();
        String grupa = studentElement.getElementsByTagName("grupa")
                .item(0)
                .getTextContent();
        String email = studentElement.getElementsByTagName("email")
                .item(0)
                .getTextContent();
        String cd = studentElement.getElementsByTagName("cd")
                .item(0)
                .getTextContent();

        Student s= new Student(nume, prenume, grupa, email, cd);
        s.setId(Long.parseLong(id));
        return s;
    }

    @Override
    public Student save(Student entity) {
        Student student = super.save(entity);
        if (student == null) {
            writeData();
        }
        return student;
    }

    @Override
    public Student delete(Long id) {
        Student result = super.delete(id);
        if(result != null){
            writeData();
        }
        return result;
    }

    @Override
    public Student update(Student entity) {
        Student result = super.update(entity);
        if(result == null){
            writeData();
        }
        return result;
    }

    private void writeData() {
        try{
            Document document = DocumentBuilderFactory.newInstance().newDocumentBuilder().newDocument();
            Element root = document.createElement("students");
            document.appendChild(root);
            for (Student s: findAll()) {
                Element e = createElementFromStudent(document, s);
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

    private Element createElementFromStudent(Document document, Student student) {
        Element element = document.createElement("student");
        element.setAttribute("id", student.getId().toString());

        Element name = document.createElement("nume");
        name.setTextContent(student.getNume());
        element.appendChild(name);

        Element prenume = document.createElement("prenume");
        prenume.setTextContent(student.getPrenume());
        element.appendChild(prenume);

        Element grupa = document.createElement("grupa");
        grupa.setTextContent(student.getGrupa());
        element.appendChild(grupa);

        Element email = document.createElement("email");
        email.setTextContent(student.getEmail());
        element.appendChild(email);

        Element cd = document.createElement("cd");
        cd.setTextContent(student.getCadruDidacticIndrumatorLab());
        element.appendChild(cd);

        return element;
    }

}
