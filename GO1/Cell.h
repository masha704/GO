class Cell
{
public:
	void set_status(size_t stat) {
		cell_stat = stat;
	}

	size_t get_stat() {
		return cell_stat;
	}

private:
	size_t cell_stat = 0; 
};
