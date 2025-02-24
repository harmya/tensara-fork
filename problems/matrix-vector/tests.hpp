#include "core.hpp"

template<typename T>
class MatrixVectorTest: public TestCase<T> {
public:
    using kernel_func_t = void (*)(T*, T*, T*, size_t, size_t);
    
    MatrixVectorTest(size_t m, size_t k) {
        this->problem_size_ = m * k;
        this->name_ = std::to_string(m) + "x" + std::to_string(k) + " x " + std::to_string(k) + "x1";
        
        auto matrix_shape = std::vector<size_t>{m, k};

        this->inputs_ = {
            std::make_shared<Tensor<T>>(matrix_shape),
            std::make_shared<Tensor<T>>(std::vector<size_t>{k})
        };
        this->outputs_ = {
            std::make_shared<Tensor<T>>(std::vector<size_t>{m})
        };
    }
    
    void prepare_data(T** host_inputs, T** host_outputs) override {
        const size_t m = this->inputs_[0]->shape()[0];
        const size_t k = this->inputs_[0]->shape()[1];
        
        for (size_t i = 0; i < m; i++) {
            for (size_t j = 0; j < k; j++) {
                host_inputs[0][i * k + j] = static_cast<T>(i + j);
            }
        }
        
        for (size_t i = 0; i < k; i++) {
            host_inputs[1][i] = static_cast<T>(i);
        }
    }
    
    std::string get_name() const override {
        return this->name_;
    }

    size_t calculate_flops() const override {
        const size_t m = this->inputs_[0]->shape()[0];
        const size_t k = this->inputs_[0]->shape()[1];
        return m * k * 2;
    }

    std::vector<size_t> get_sizes() const override {
        const size_t m = this->inputs_[0]->shape()[0];
        const size_t k = this->inputs_[0]->shape()[1];
        return {m, k};
    }

    void launch_kernel(const std::vector<T*>& inputs, const std::vector<T*>& outputs, 
                      const std::vector<size_t>& sizes, void* kernel_func) override {
        auto typed_func = reinterpret_cast<kernel_func_t>(kernel_func);
        typed_func(inputs[0], inputs[1], outputs[0], sizes[0], sizes[1]);
    }
};

std::vector<std::unique_ptr<TestCase<float>>> create_test_cases() {
    std::vector<std::unique_ptr<TestCase<float>>> test_cases;
    
    test_cases.push_back(std::make_unique<MatrixVectorTest<float>>(4096, 4096));
    test_cases.push_back(std::make_unique<MatrixVectorTest<float>>(6144, 4096));
    test_cases.push_back(std::make_unique<MatrixVectorTest<float>>(7168, 4096));
    test_cases.push_back(std::make_unique<MatrixVectorTest<float>>(8192, 4096));
    test_cases.push_back(std::make_unique<MatrixVectorTest<float>>(9216, 4096));
    return test_cases;
}
