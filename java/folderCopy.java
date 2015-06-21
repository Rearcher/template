import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.util.Scanner;

/**
 * Created by Huan on 2015/6/21.
 */
public class folderCopy {

    public void fileCopy(File src, File dest) throws Exception {
        FileInputStream input = null;
        FileOutputStream output = null;
        try {
            input = new FileInputStream(src);
            output = new FileOutputStream(dest);
            input.getChannel().transferTo(0,input.getChannel().size(),output.getChannel());
        }
        catch (Exception e){
            throw e;
        }
        finally {
            output.close();
            input.close();
        }
    }

    public void folderCopy(String srcFolder, String destFolder) throws Exception{
        (new File(destFolder)).mkdirs();
        File[] files = (new File(srcFolder)).listFiles();
        for(File single : files) {
            if(single.isFile()) {
                File destFile = new File(new File(destFolder).getAbsolutePath()+File.separator+single.getName());
                fileCopy(single, destFile);
            }
            else if(single.isDirectory()){
                String dir1 = srcFolder+"/"+single.getName();
                String dir2 = destFolder+"/"+single.getName();
                folderCopy(dir1,dir2);
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Scanner scanner = new Scanner(System.in);
        String src, dest;
        System.out.println("Enter source folder and destination folder:");
        src = scanner.next();
        dest = scanner.next();

        File[] files = (new File(src)).listFiles();
        for(File single : files) {
            if(single.isFile()) {
                new folderCopy().fileCopy(single, new File(dest+File.separator+single.getName()));
            }
            else if(single.isDirectory()) {
                String srcFolder = src + "/" + single.getName();
                String destFolder = dest + "/" + single.getName();
                new folderCopy().folderCopy(srcFolder, destFolder);
            }
        }

        scanner.close();
        System.out.println("Completed!");
    }
}
