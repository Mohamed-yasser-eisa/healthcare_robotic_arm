close all; clear;
theta1=0;d1=0;a1=0;alpha1=90 ;      %parameter link1

theta2=0;d2=35;a2=0;alpha2=-90;     %parameter link2

theta3=0;d3=0;a3=15;alpha3=0;         %parameter link3

theta4=0;d4=0;a4=10;alpha4=90;       %parameter link4

deltatheta1=0;deltatheta2=0; deltatheta3=0; deltatheta4=0;  %theta1,2,3,4 velocity
%end-effector desired position 
Xc=40;Yc=20;
a=0;b=0;
while a==0
    while b==0;
	% updating joint angeles
        theta1=theta1+deltatheta1/2;
        theta2=theta2+deltatheta2/2;
        theta3=theta3+deltatheta3/2;
        theta4=theta4+deltatheta4/2;   %360-theta1-theta2;
        
        theta = [theta1 theta2 theta3 theta4 ]
        disp('theta:');disp(theta);
        
	%Calculating the DH matrix for each joint
        T01=DHmatrix(theta1,d1,a1,alpha1);
        T12=DHmatrix(theta2,d2,a2,alpha2);
        T23=DHmatrix(theta3,d3,a3,alpha3);
        T34=DHmatrix(theta4,d4,a4,alpha4);
        T02=T01*T12;
        T03=T01*T12*T23;
        T04=T01*T12*T23*T34;
        P0=[0 0];
        P1=transpose(T01(1:2,4));
        P2=transpose(T02(1:2,4));
        P3=transpose(T03(1:2,4));
        P4=transpose(T04(1:2,4));

        Q1=[P0(1,1) P1(1,1) P2(1,1) P3(1,1) P4(1,1)];
        Q2=[P0(1,2) P1(1,2) P2(1,2) P3(1,2) P4(1,2)];
        disp('end effector pos:');disp(T03);
        
        plot(Q1,Q2,'-o','LineWidth',4);
        axis([-60,60,-60,60]);
        grid on;
        
    
        %Linear velocity jacobian
        %Prismatic: Jv = zi-1
        %Revolute: Jv = zi-1 x (on - oi-1)

        %jcaobian for 1st link
        Z0=[0;0;1];O=[0;0;0];O4=T04(1:3,4);
        Jv1=cross(Z0,(O4-O));

        %jcaobian for 2nd link
        Z1=T01(1:3,3);O1=T01(1:3,4);
        Jv2=cross(Z1,(O4-O1));

        %jcaobian for 3rd link
        Z2=T12(1:3,3);O2=T12(1:3,4);
        Jv3=cross(Z2,(O4-O2));
	
        %jcaobian for 4th link
        Z3=T23(1:3,3);O3=T23(1:3,4);
        Jv4=cross(Z3,(O4-O3));
		
        Jv=[Jv1 Jv2 Jv3 Jv4];
        disp('Jv:'); disp(Jv);
        
        Xinit=P4(1,1);Yinit=P4(1,2);
        Xend=Xc;Yend=Yc; 
        Xspeed=(Xend-Xinit)/20;
        Yspeed=(Yend-Yinit)/20;

        %Pseudoinverse Jacobian
        thetadot=pinv(Jv)*[Xspeed;Yspeed;0];
        OrinEnd=atan2d(Yend,Xend);
        Orininit=atan2d(Yinit,Xinit);
        dis_error=sqrt(Xend^2+Yend^2)- sqrt(Xinit^2+Yinit^2);
        orin_error=OrinEnd-Orininit;
        if abs(dis_error)<=0.2 && abs(orin_error)<=2
            b=1;
        end
        theta1dot=thetadot(1,1);
        theta2dot=thetadot(2,1);
        theta3dot=thetadot(3,1);
        theta4dot=thetadot(4,1);

        disp('thetadot:');disp(thetadot);
       
        deltatheta1=radtodeg(theta1dot);
        deltatheta2=radtodeg(theta2dot);
        deltatheta3=radtodeg(theta3dot);
        deltatheta4=radtodeg(theta4dot);
       
        deltatheta=[deltatheta1;deltatheta2;deltatheta3;deltatheta4];
        disp('deltatheta');disp(deltatheta);
        text(P4(1,1),P4(1,2),['  (', num2str(P4(1,1),3), ', ', num2str(P4(1,2),3), ')']);
        text(-25,-17,'Orinerror:','Color','red','FontSize',12)
        text(-25,-25,num2str(abs(orin_error),3),'Color','red','FontSize',12)
        text(-25,-30,'diserror:','Color','red','FontSize',12)
        text(-25,-38,num2str(abs(dis_error),3),'Color','red','FontSize',12)
        pause(0.01);
        
        
    end
    if b==1
       [Xc,Yc,buttons] = ginput;
       b=0;
    end
end
