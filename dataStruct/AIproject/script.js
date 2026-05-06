document.addEventListener('DOMContentLoaded', function() {
    const loginBtn = document.getElementById('loginBtn');
    const captchaModal = document.getElementById('captchaModal');
    const successModal = document.getElementById('successModal');
    const closeBtn = document.querySelector('.close');
    const sliderBtn = document.getElementById('sliderBtn');
    const sliderTrack = document.querySelector('.slider-track');
    const captchaStatus = document.getElementById('captchaStatus');
    const canvas = document.getElementById('captchaCanvas');
    const ctx = canvas.getContext('2d');

    let isDragging = false;
    let startX = 0;
    let currentX = 0;
    let puzzleX = 0;
    let puzzleY = 0;
    let puzzleWidth = 50;
    let puzzleHeight = 50;
    let isVerified = false;

    // 生成拼图验证码
    function generateCaptcha() {
        const width = canvas.width;
        const height = canvas.height;
        
        // 清空画布
        ctx.clearRect(0, 0, width, height);
        
        // 绘制背景
        const gradient = ctx.createLinearGradient(0, 0, width, height);
        gradient.addColorStop(0, '#667eea');
        gradient.addColorStop(1, '#764ba2');
        ctx.fillStyle = gradient;
        ctx.fillRect(0, 0, width, height);
        
        // 添加一些干扰元素
        for (let i = 0; i < 20; i++) {
            ctx.beginPath();
            ctx.arc(
                Math.random() * width,
                Math.random() * height,
                Math.random() * 3 + 1,
                0,
                Math.PI * 2
            );
            ctx.fillStyle = `rgba(255, 255, 255, ${Math.random() * 0.3})`;
            ctx.fill();
        }
        
        // 生成拼图块位置
        puzzleX = Math.random() * (width - puzzleWidth - 100) + 50;
        puzzleY = Math.random() * (height - puzzleHeight - 20) + 10;
        
        // 绘制拼图块
        drawPuzzle(puzzleX, puzzleY, puzzleWidth, puzzleHeight, '#ffffff');
        
        // 绘制目标位置（左边）
        drawTargetSlot(10, puzzleY, puzzleWidth, puzzleHeight);
        
        // 重置滑块
        sliderBtn.style.left = '0px';
        sliderBtn.textContent = '拖动验证';
        sliderBtn.classList.remove('verified');
        captchaStatus.textContent = '请拖动滑块完成验证';
        captchaStatus.className = 'status';
        isVerified = false;
    }

    // 绘制拼图块
    function drawPuzzle(x, y, width, height, color) {
        ctx.fillStyle = color;
        ctx.beginPath();
        
        // 创建拼图形状
        ctx.moveTo(x, y);
        ctx.lineTo(x + width * 0.7, y);
        
        // 凸起部分
        ctx.bezierCurveTo(
            x + width * 0.7, y - height * 0.2,
            x + width * 0.9, y - height * 0.2,
            x + width * 0.9, y
        );
        ctx.lineTo(x + width, y);
        ctx.lineTo(x + width, y + height * 0.7);
        
        // 凹陷部分
        ctx.bezierCurveTo(
            x + width + width * 0.2, y + height * 0.7,
            x + width + width * 0.2, y + height * 0.9,
            x + width, y + height * 0.9
        );
        ctx.lineTo(x + width, y + height);
        ctx.lineTo(x, y + height);
        ctx.lineTo(x, y + width * 0.7);
        
        // 另一个凸起
        ctx.bezierCurveTo(
            x - width * 0.2, y + height * 0.7,
            x - width * 0.2, y + height * 0.9,
            x, y + height * 0.9
        );
        ctx.lineTo(x, y + height);
        ctx.lineTo(x, y);
        
        ctx.fill();
        
        // 添加边框
        ctx.strokeStyle = '#333';
        ctx.lineWidth = 2;
        ctx.stroke();
        
        // 添加文字
        ctx.fillStyle = '#333';
        ctx.font = 'bold 14px Arial';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText('拖动', x + width / 2, y + height / 2);
    }

    // 绘制目标位置
    function drawTargetSlot(x, y, width, height) {
        ctx.strokeStyle = '#333';
        ctx.lineWidth = 2;
        ctx.setLineDash([5, 5]);
        ctx.strokeRect(x, y, width, height);
        ctx.setLineDash([]);
        
        ctx.fillStyle = 'rgba(255, 255, 255, 0.3)';
        ctx.fillRect(x, y, width, height);
        
        ctx.fillStyle = '#666';
        ctx.font = 'bold 14px Arial';
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';
        ctx.fillText('目标', x + width / 2, y + height / 2);
    }

    // 显示验证码弹窗
    function showCaptchaModal() {
        const phone = document.getElementById('phone').value;
        const password = document.getElementById('password').value;
        
        if (!phone || !password) {
            alert('请输入手机号和密码');
            return;
        }
        
        if (!validatePhone(phone)) {
            alert('请输入有效的手机号');
            return;
        }
        
        generateCaptcha();
        captchaModal.style.display = 'block';
    }

    // 验证手机号
    function validatePhone(phone) {
        const phoneRegex = /^1[3-9]\d{9}$/;
        return phoneRegex.test(phone);
    }

    // 关闭验证码弹窗
    function closeCaptchaModal() {
        captchaModal.style.display = 'none';
    }

    // 滑块拖动事件
    sliderBtn.addEventListener('mousedown', startDrag);
    sliderBtn.addEventListener('touchstart', startDrag);

    function startDrag(e) {
        if (isVerified) return;
        
        isDragging = true;
        sliderBtn.classList.add('dragging');
        
        const event = e.type === 'touchstart' ? e.touches[0] : e;
        startX = event.clientX;
        
        document.addEventListener('mousemove', drag);
        document.addEventListener('mouseup', stopDrag);
        document.addEventListener('touchmove', drag);
        document.addEventListener('touchend', stopDrag);
    }

    function drag(e) {
        if (!isDragging || isVerified) return;
        
        e.preventDefault();
        
        const event = e.type === 'touchmove' ? e.touches[0] : e;
        currentX = event.clientX - startX;
        
        const maxDrag = sliderTrack.offsetWidth - sliderBtn.offsetWidth;
        
        if (currentX < 0) currentX = 0;
        if (currentX > maxDrag) currentX = maxDrag;
        
        sliderBtn.style.left = currentX + 'px';
        
        // 更新画布上的拼图块位置
        const progress = currentX / maxDrag;
        const newPuzzleX = 10 + (puzzleX - 10) * progress;
        
        // 重绘验证码
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        const gradient = ctx.createLinearGradient(0, 0, canvas.width, canvas.height);
        gradient.addColorStop(0, '#667eea');
        gradient.addColorStop(1, '#764ba2');
        ctx.fillStyle = gradient;
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        
        // 添加干扰元素
        for (let i = 0; i < 20; i++) {
            ctx.beginPath();
            ctx.arc(
                Math.random() * canvas.width,
                Math.random() * canvas.height,
                Math.random() * 3 + 1,
                0,
                Math.PI * 2
            );
            ctx.fillStyle = `rgba(255, 255, 255, ${Math.random() * 0.3})`;
            ctx.fill();
        }
        
        drawTargetSlot(10, puzzleY, puzzleWidth, puzzleHeight);
        drawPuzzle(newPuzzleX, puzzleY, puzzleWidth, puzzleHeight, '#ffffff');
    }

    function stopDrag() {
        if (!isDragging) return;
        
        isDragging = false;
        sliderBtn.classList.remove('dragging');
        
        document.removeEventListener('mousemove', drag);
        document.removeEventListener('mouseup', stopDrag);
        document.removeEventListener('touchmove', drag);
        document.removeEventListener('touchend', stopDrag);
        
        // 检查是否验证成功
        const maxDrag = sliderTrack.offsetWidth - sliderBtn.offsetWidth;
        const tolerance = 5; // 容差范围
        
        if (currentX >= maxDrag - tolerance) {
            // 验证成功
            isVerified = true;
            sliderBtn.classList.add('verified');
            sliderBtn.textContent = '✓';
            captchaStatus.textContent = '验证成功！';
            captchaStatus.className = 'status success';
            
            // 延迟显示成功弹窗
            setTimeout(() => {
                closeCaptchaModal();
                showSuccessModal();
            }, 500);
        } else {
            // 验证失败，重置
            captchaStatus.textContent = '验证失败，请重试';
            captchaStatus.className = 'status error';
            
            setTimeout(() => {
                sliderBtn.style.left = '0px';
                generateCaptcha();
            }, 1000);
        }
        
        currentX = 0;
    }

    // 显示成功弹窗
    function showSuccessModal() {
        successModal.style.display = 'block';
        
        // 模拟提交登录信息
        setTimeout(() => {
            const phone = document.getElementById('phone').value;
            const password = document.getElementById('password').value;
            
            console.log('提交登录信息:');
            console.log('手机号:', phone);
            console.log('密码:', password);
            
            // 这里可以添加实际的登录逻辑
            alert('登录信息已提交！\n手机号: ' + phone);
            
            successModal.style.display = 'none';
            
            // 清空表单
            document.getElementById('phone').value = '';
            document.getElementById('password').value = '';
        }, 2000);
    }

    // 事件监听
    loginBtn.addEventListener('click', showCaptchaModal);
    closeBtn.addEventListener('click', closeCaptchaModal);
    
    // 点击弹窗外部关闭
    window.addEventListener('click', function(e) {
        if (e.target === captchaModal) {
            closeCaptchaModal();
        }
    });
    
    // 键盘事件
    document.addEventListener('keydown', function(e) {
        if (e.key === 'Escape') {
            closeCaptchaModal();
        }
    });
    
    // 回车键登录
    document.getElementById('password').addEventListener('keypress', function(e) {
        if (e.key === 'Enter') {
            showCaptchaModal();
        }
    });
});