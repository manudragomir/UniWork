package domain;

import com.sun.javafx.collections.MappingChange;
import javafx.util.Pair;
import org.apache.commons.codec.digest.DigestUtils;
import utils.Privilegii;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.HashMap;
import java.util.Map;


public class LoginData {
    Map<String, Pair<String, Privilegii>> users = new HashMap<>();

    public LoginData() throws NoSuchAlgorithmException {
        users.put("admin", new Pair<>(DigestUtils.md5Hex("admin").toUpperCase(), Privilegii.ADMIN));
        users.put("prof", new Pair<>(DigestUtils.md5Hex("prof").toUpperCase(), Privilegii.PROF));
        users.put("dmir2503", new Pair<>(DigestUtils.md5Hex("stud").toUpperCase(), Privilegii.STUD));
    }

    public Privilegii checkData(String user, String parola){
        if(users.get(user) != null && users.get(user).getKey().equals(DigestUtils.md5Hex(parola).toUpperCase())){
            return users.get(user).getValue();
        }
        return Privilegii.EXTERN;
    }
}
