from genllheaders import main


def test_main(data, hal_path, tmp_path):
    """Test that common LL headers are generated correctly."""

    main(hal_path, tmp_path)

    # check README file
    ref_readme_file = data / "README.rst"
    gen_readme_file = tmp_path / "README.rst"

    assert gen_readme_file.exists()

    with open(ref_readme_file) as ref, open(gen_readme_file) as gen:
        assert ref.read() == gen.read()

    # check tim file
    ref_tim_file = data / "stm32_ll_tim.h"
    gen_tim_file = tmp_path / "include" / "stm32_ll_tim.h"

    assert gen_tim_file.exists()

    with open(ref_tim_file) as ref, open(gen_tim_file) as gen:
        assert ref.read() == gen.read()

    # check usart file
    ref_usart_file = data / "stm32_ll_usart.h"
    gen_usart_file = tmp_path / "include" / "stm32_ll_usart.h"

    assert gen_usart_file.exists()

    with open(ref_usart_file) as ref, open(gen_usart_file) as gen:
        assert ref.read() == gen.read()

    # check usb file is not created (ignore list)
    gen_usb_file = tmp_path / "include" / "stm32_ll_usb.h"

    assert not gen_usb_file.exists()
