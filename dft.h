namespace dft {
    double map(int value, int old_min, int old_max, int new_min, int new_max) {
        if (value > old_max) {
            return new_max;
        }
        if (value < old_min) {
            return new_min;
        }
        double old_delta = double(value) / (old_max - old_min);
        int new_delta = new_max - new_min;
        return int(new_delta * old_delta + new_min);
    }
}
