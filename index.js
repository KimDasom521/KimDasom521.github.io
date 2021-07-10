window.onload = function () {
    var desc = [document.getElementById('book1_desc').innerText,
    "문산수억고등학교 웹페이지 멘토링입니다.",
    "잘 부탁드립니다!"]; // 문자열 목록
    var index = 0;

    var interval = setInterval(function() {
        $('#book1_desc').fadeOut(500, function() {
            // 지금 표시된 문자가 사라지면 수행할 작업
            index++; // 0 >> 1
            if (index === desc.length)
                index = 0;
            $(this).text(desc[index]).fadeIn(500);
        });
    }, 4000);

    var leftarrow = document.getElementById('left-arrow');
    var rightarrow = document.getElementById('right-arrow');

    leftarrow.onclick = function () {
        $('#book1_desc').fadeOut(500,function() {
            index--;
            if (index === -1)
                index = 2;
            $(this).text(desc[index]).fadeIn(500);
            clearInterval(interval); // 문자열 자동변환 주기를 초기화
            interval = setInterval(function() {
                $('#book1_desc').fadeOut(500, function() {
                    // 지금 표시된 문자가 사라지면 수행할 작업
                    index++; // 0 >> 1
                    if (index === desc.length)
                        index = 0;
                    $(this).text(desc[index]).fadeIn(500);
                });
            }, 4000);
        })
    }

    rightarrow.onclick = function () {
        $('#book1_desc').fadeOut(500,function() {
            index++;
            if (index === desc.length)
                index = 0;
            $(this).text(desc[index]).fadeIn(500);
            clearInterval(interval); // 문자열 자동변환 주기를 초기화
            interval = setInterval(function() {
                $('#book1_desc').fadeOut(500, function() {
                    // 지금 표시된 문자가 사라지면 수행할 작업
                    index++; // 0 >> 1
                    if (index === desc.length)
                        index = 0;
                    $(this).text(desc[index]).fadeIn(500);
                });
            }, 4000);
        })
    }

}