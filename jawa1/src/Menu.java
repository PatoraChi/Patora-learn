
import java.util.Scanner;

public class Menu {
public int Pilihan;

    public Menu(){
        this.tampilkanMenu();
    }
    private  void tampilkanMenu(){
        Scanner scanner = new Scanner(System.in);
        do {
            System.out.println("1. Tambah Data");
            System.out.println("2. Keluar");
            System.err.print("Pilihan : ");
            this.Pilihan = scanner.nextInt();
           
            scanner.nextLine();
            
            if(this.Pilihan == 1){
                Mahasiswa MahasiswaBaru = new Mahasiswa();
            }

        } while (this.Pilihan != 2);
        scanner.close();
        scanner.close();
    }
}
