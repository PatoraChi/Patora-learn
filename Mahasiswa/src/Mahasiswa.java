import java.util.Scanner;

public class Mahasiswa {
    public String NIM;
    public String Nama;
    public String TahunMasuk;
    public float IPK;

    public Mahasiswa(){
        this.tambahdata();
    }
    
    
    private  void tambahdata(){
        Scanner scanner = new Scanner(System.in);
        System.out.print("Masukan Nama : ");
        String nama = scanner.nextLine();

        System.out.print("Masukan NIM : ");
        String nim = scanner.nextLine();

        System.out.print("Masukan Tahun Masuk : ");
        String tahunMasuk = scanner.nextLine();
        
        System.out.print("Masukan IPK : ");
        float ipk = scanner.nextFloat();
        System.out.println("Nama: "+nama);
        System.out.println("Nim: "+nim);
        System.out.println("Tahun Masuk: "+tahunMasuk);
        System.out.println("IPK: "+ipk);


    }
}
