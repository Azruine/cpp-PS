class ProductOfNumbers
{
private:
    int size = 0;
    int lastZero = 0;
    std::vector<int> data;
    std::vector<int> suffixMul;

public:
    ProductOfNumbers()
    {
        lastZero = 0;
        size = 0;
        data.clear();
        suffixMul.clear();
    }

    void add(int num)
    {
        size++;
        data.emplace_back(num);
        if (num == 0)
        {
            lastZero = size;
            suffixMul.clear();
        }
        else if (suffixMul.empty())
            suffixMul.emplace_back(num);
        else
            suffixMul.emplace_back(suffixMul.back() * num);
    }

    int getProduct(int k)
    {
        assert(size >= k);
        int temp = suffixMul.size();
        if (k > temp)
            return 0;
        else if (temp == k)
            return suffixMul[temp - 1];
        else
            return suffixMul[temp - 1] / suffixMul[temp - k - 1];
    }
};