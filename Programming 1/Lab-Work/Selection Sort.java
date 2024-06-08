import java.util.List;

public class Sort {
	
	public static void selectionSort(List<Integer> list) {
		if (list.size() != 0) {
			int boundary = 0;
			int end = list.size();
			while (boundary != end) {
				int smallest_id = boundary;
				for (int id = boundary; id < end; id++) {
					if (list.get(id) < list.get(smallest_id)) {
						smallest_id = id;
					}
				}
				int set_var = list.get(boundary);
				list.set(boundary, list.get(smallest_id));
				list.set(smallest_id, set_var);
				boundary += 1;

			}
		}
	}

	//Add your method here.
	
	
	public static void main(String[] args) {
		//Sort it out.
	}
	
}
